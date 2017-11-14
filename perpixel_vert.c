// PER-PIXEL Lighting
// �wiat�o kierunkowe!

varying vec3 normal;		// Do fragment shadera

void main() {
	// Wektor normalny (b�dzie interpolowany):
	normal = gl_NormalMatrix * gl_Normal;

	vec4 a = gl_Vertex;
	/*
	a.x = a.x * 0.5;
	a.y = a.y * 0.5;
	a.z = a.z * 0.5;
*/
	gl_Position = gl_ModelViewProjectionMatrix * a;

	// Pozycja vertexa bez zmian:
	//gl_Position = ftransform();

}
