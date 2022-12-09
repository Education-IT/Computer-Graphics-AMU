#version 430 core
uniform vec3 color;
out vec4 out_color;
float near = 0.3;
float far = 70;

float gl_zz(float depth){
float x  = depth * 2.0 - 1.0;
float z = -1*((near+far)/(near-far)) - ((2*near*far)/depth*(near-far)); //
//return -1*((2.0 * near * far) / (far + near + z * (near - far)));
 return (2.0 * near * far) / (far + near - x * (far - near));
}

void main()
{

	//float  depth = gl_zz(gl_FragCoord.z) / far;
	//vec3 tlo = vec3(0.0f, 0.3f, 0.3f);
	//vec3 KOLOR = depth*tlo;
	//out_color = vec4(vec3(KOLOR),1.0);  
	
	out_color = vec4(color,1); //
}
