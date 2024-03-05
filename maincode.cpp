void lookat(const vec3 eye, const vec3 center, const vec3 up) { // check https://github.com/ssloy/tinyrenderer/wiki/Lesson-5-Moving-the-camera
    vec3 z = (center-eye).normalized();
    vec3 x =  cross(up,z).normalized();
    vec3 y =  cross(z, x).normalized();
    mat<4,4> Minv = {{{x.x,x.y,x.z,0},   {y.x,y.y,y.z,0},   {z.x,z.y,z.z,0},   {0,0,0,1}}};
    mat<4,4> Tr   = {{{1,0,0,-eye.x}, {0,1,0,-eye.y}, {0,0,1,-eye.z}, {0,0,0,1}}};
    ModelView = Minv*Tr;
}

vec3 barycentric(const vec2 tri[3], const vec2 P) {
    mat<3,3> ABC = {{embed<3>(tri[0]), embed<3>(tri[1]), embed<3>(tri[2])}};
    if (ABC.det()<1e-3) return {-1,1,1}; // for a degenerate triangle generate negative coordinates, it will be thrown away by the rasterizator
    return ABC.invert_transpose() * embed<3>(P);
}

void triangle(const vec4 clip_verts[3], IShader &shader, TGAImage &image, std::vector<double> &zbuffer) {
    vec4 pts[3]  = { Viewport*clip_verts[0],    Viewport*clip_verts[1],    Viewport*clip_verts[2]    };  // triangle screen coordinates before persp. division
    vec2 pts2[3] = { proj<2>(pts[0]/pts[0][3]), proj<2>(pts[1]/pts[1][3]), proj<2>(pts[2]/pts[2][3]) };  // triangle screen coordinates after  perps. division
//hello
   virtual void vertex(const int iface, const int nthvert, vec4& gl_Position) {
        varying_uv.set_col(nthvert, model.uv(iface, nthvert));
        varying_nrm.set_col(nthvert, proj<3>((ModelView).invert_transpose()*embed<4>(model.normal(iface, nthvert), 0.)));
        gl_Position= ModelView*embed<4>(model.vert(iface, nthvert));
        view_tri.set_col(nthvert, proj<3>(gl_Position));
        gl_Position = Projection*gl_Position;
    }
