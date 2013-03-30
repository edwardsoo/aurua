#ifndef GEOMETRY_H_
#define GEOMETRY_H_

// return a vector c on line a_b
// c is 'length' distance away from a
Vec3 normalize(Vec3 a, Vec3 b, double length) {
	Vec3 a_b = b - a;
	a_b.normalize();
	Vec3 c = a_b * length + a;
	return c;
}

void draw_crosshair(int screen_width, int screen_height) {
	float h_w_ratio = float(screen_height) / screen_width;
	glColor4f(0.2, 0.5, 0, 0.5);
	glBegin (GL_LINES);
	glVertex3f(0, -0.05, 0);
	glVertex3f(0, -0.01, 0);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(0, 0.01, 0);
	glVertex3f(0, 0.05, 0);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(-0.05 * h_w_ratio, 0, 0);
	glVertex3f(-0.01 * h_w_ratio, 0, 0);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(0.01 * h_w_ratio, 0, 0);
	glVertex3f(0.05 * h_w_ratio, 0, 0);
	glEnd();
}

void draw_quarter_hemisphere(float radius, int stacks) {
	float tri_h = radius / stacks;
	float tri_d = radius / (sqrt(2) * stacks);
	float tri_w = 2 * radius / (sqrt(2) * stacks);
	float i, j;
	float s0_x0, s1_x0, s0_y, s1_y, s0_z, s1_z;
	double s0_du, s1_du, s0_v, s1_v;
	Vec3 a, b, c;
	a = Vec3(0, 0, 0);
	for (i = 1; i <= stacks; i++) {
		s0_x0 = -(i - 1) * tri_d;
		s1_x0 = -i * tri_d;
		s0_y = radius - tri_h * (i - 1);
		s1_y = radius - tri_h * i;
		s0_z = tri_d * (i - 1);
		s1_z = tri_d * i;
		s0_du = ((i - 1) >= 1) ? (1.0 / (i - 1)) : 0.5;
		s1_du = 1.0 / i;
		s0_v = ((i - 1) / stacks);
		s1_v = (i / stacks);
		glBegin (GL_TRIANGLE_STRIP);
		for (j = 1; j <= i; j++) {
			b = Vec3(s1_x0 + (j - 1) * tri_w, s1_y, s1_z);
			c = normalize(a, b, radius);
			glNormal3f(c.x, c.y, c.z);
			glTexCoord2f((j - 1) * s1_du, s1_v);
			glVertex3f(c.x, c.y, c.z);

			b = Vec3(s0_x0 + (j - 1) * tri_w, s0_y, s0_z);
			c = normalize(a, b, radius);
			glNormal3f(c.x, c.y, c.z);
			glTexCoord2f((j - 1) * s0_du, s0_v);
			glVertex3f(c.x, c.y, c.z);
		}
		b = Vec3(s1_x0 + i * tri_w, s1_y, s1_z);
		c = normalize(a, b, radius);
		glNormal3f(c.x, c.y, c.z);
		glTexCoord2f(1, s1_v);
		glVertex3f(c.x, c.y, c.z);

		glEnd();
	}
}

void draw_hemisphere_point(Vec3 b, float radius, float u, float v) {
	b.normalize();
	Vec3 c = b * radius;
	glNormal3f(c.x, c.y, c.z);
	glTexCoord2f(u, v);
	glVertex3f(c.x, c.y, c.z);
}

void draw_quarter1(float radius, int stacks, float tri_h, float tri_w,
		float tri_d, float i) {
	Vec3 a, b, c;
	a = Vec3(0, 0, 0);
	float s0_x0, s1_x0, s0_y, s1_y, s0_z, s1_z;
	double s0_du, s1_du, s0_v, s1_v, j;
	s0_x0 = -(i - 1) * tri_d;
	s1_x0 = -i * tri_d;
	s0_y = radius - tri_h * (i - 1);
	s1_y = radius - tri_h * i;
	s0_z = tri_d * (i - 1);
	s1_z = tri_d * i;
	s0_du = ((i - 1) >= 1) ? (1.0 / (i - 1)) : 0.5;
	s1_du = 1.0 / i;
	s0_v = ((i - 1) / stacks);
	s1_v = (i / stacks);
	for (j = 1; j <= i; j++) {
		b = Vec3(s1_x0 + (j - 1) * tri_w, s1_y, s1_z);
		draw_hemisphere_point(b, radius, (j - 1) * s1_du, s1_v);

		b = Vec3(s0_x0 + (j - 1) * tri_w, s0_y, s0_z);
		draw_hemisphere_point(b, radius, (j - 1) * s0_du, s0_v);
	}
	b = Vec3(s1_x0 + i * tri_w, s1_y, s1_z);
	draw_hemisphere_point(b, radius, 1, s1_v);
}

void draw_hemisphere(float radius, int stacks) {
	float tri_h = radius / stacks;
	float tri_d = radius / (sqrt(2) * stacks);
	float tri_w = 2 * radius / (sqrt(2) * stacks);
	float i;
	for (i = 1; i <= stacks; i++) {
		glBegin (GL_TRIANGLE_STRIP);
		draw_quarter1(radius, stacks, tri_h, tri_w, tri_d, i);
		// not done
		glEnd();
	}
}

void draw_quarter_octahedron(float radius, int stacks) {
	float tri_h = radius / stacks;
	float tri_d = radius / (sqrt(2) * stacks);
	float tri_w = 2 * radius / (sqrt(2) * stacks);
	float i, j;
	float s0_x0, s1_x0, s0_y, s1_y, s0_z, s1_z;
	double s0_du, s1_du, s0_v, s1_v;
	Vec3 a, b, c;
	a = Vec3(0, 0, 0);
	for (i = 1; i <= stacks; i++) {
		s0_x0 = -(i - 1) * tri_d;
		s1_x0 = -i * tri_d;
		s0_y = radius - tri_h * (i - 1);
		s1_y = radius - tri_h * i;
		s0_z = tri_d * (i - 1);
		s1_z = tri_d * i;
		s0_du = ((i - 1) >= 1) ? (1.0 / (i - 1)) : 0;
		s1_du = 1.0 / i;
		s0_v = ((i - 1) / stacks);
		s1_v = (i / stacks);
		glBegin (GL_TRIANGLE_STRIP);
		for (j = 1; j <= i; j++) {
			b = Vec3(s1_x0 + (j - 1) * tri_w, s1_y, s1_z);
			glNormal3f(b.x, b.y, b.z);
			glTexCoord2f((j - 1) * s1_du, s1_v);
			glVertex3f(b.x, b.y, b.z);

			b = Vec3(s0_x0 + (j - 1) * tri_w, s0_y, s0_z);
			glNormal3f(b.x, b.y, b.z);
			glTexCoord2f((j - 1) * s0_du, s0_v);
			glVertex3f(b.x, b.y, b.z);
		}
		b = Vec3(s1_x0 + i * tri_w, s1_y, s1_z);
		glNormal3f(b.x, b.y, b.z);
		glTexCoord2f(1, s1_v);
		glVertex3f(b.x, b.y, b.z);
		glEnd();
	}
}

#endif
