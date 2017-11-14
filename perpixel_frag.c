// PER-PIXEL Lighting
// swiatlo kierunkowe!

varying vec3 normal;		// Z vertex shadera
vec3 lightDir;
float NdotHV, specular;
vec4 kolor;

void main() {
	float jasnosc;
	// Normalizacja interpolowanej normalnej:
	vec3 n = normalize(normal);
	// Wektor padania �wiat�a (dla ka�dego wierzcho�ka taki sam):
	lightDir = normalize(vec3(gl_LightSource[0].position));
	// Iloczyn skalarny znormalizowanych wektor�w,
	// wartosci ujemne zostan� zast�pione zerem:
	jasnosc = max(dot(lightDir, n), 0.0);

	// Odbicie zwierciadlane -> algorytm Blinna-Phonga.
	// Wyliczenie jasno�ci rozb�ysku jako iloczynu skalarnego
	// wektora po�owicznego i normalnej w danym punkcie:
	NdotHV = max(dot(n, gl_LightSource[0].halfVector.xyz), 0.0);
	// Pot�ga -> wsp��czynnik skupienia plamy �wiat�a:
	specular = pow(NdotHV, 16.0);

	// Odcie� koloru (R) na podstawie jasno�ci:
	kolor = vec4(jasnosc, jasnosc*0.5, 0.0, 0.0);
	if(jasnosc > 0.995)
		kolor += vec4(1.0,1.0,1.0,1.0);
	else if (jasnosc > 0.95)
		kolor += vec4(1.0,1.0,1.0,1.0) * kolor;
	else if (jasnosc > 0.4)
		kolor += vec4(0.7,0.7,0.7,1.0) * kolor;
	else if (jasnosc > 0.1)
		kolor += vec4(0.35,0.35,0.35,1.0) * kolor;
	else
		kolor += vec4(0.1,0.1,0.1,1.0) * kolor;

	kolor = floor(jasnosc * float(5) + 0.5) / float(5) *kolor;

	gl_FragColor = kolor;
}
