// simple fragment shader

uniform int n;

void main()
{
	if(int(gl_FragCoord.y)%n != 0) discard;
	gl_FragColor = gl_Color;
}
