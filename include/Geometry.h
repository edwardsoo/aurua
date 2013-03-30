#ifndef GEOMETRY_H_
#define GEOMETRY_H_

Vec3 normalize(Vec3 a, Vec3 b, double length) {
// get the distance between a and b along the x and y axes
	Vec3 a_b = b - a;
	a_b.normalize();
	Vec3 c = a_b * length + a;
	return c;
}

void draw_hemisphere(float radius, int stacks) {
	float tri_h = radius / stacks;
	float tri_d = radius / (sqrt(2) * stacks);
	float tri_w = 2 * radius / (sqrt(2) * stacks);
	float i, j, x, y, z;
	float s0_x0, s1_x0, s0_y, s1_y, s0_z, s1_z;
	for (i = 1; i <= stacks; i++) {
		s0_x0 = -(i - 1) * tri_d;
		s1_x0 = -i * tri_d;
		s0_y = radius - tri_h * (i - 1);
		s1_y = radius - tri_h * i;
		s0_z = tri_d * (i - 1);
		s1_z = tri_d * i;
		glBegin (GL_TRIANGLE_STRIP);
		for (j = 1; j <= i; j++) {
			glVertex3f(s1_x0 + (j - 1) * tri_w, s1_y, s1_z);

			glVertex3f(s0_x0 + (j - 1) * tri_w, s0_y, s0_z);
		}
		glVertex3f(s1_x0 + i * tri_w, s1_y, s1_z);
		glEnd();
	}
}

#endif
