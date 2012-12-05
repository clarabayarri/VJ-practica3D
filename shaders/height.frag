varying float height;
uniform float miny;
uniform float maxy;
uniform sampler2D tex1;
uniform sampler2D tex2;

void main(){
	float h = (height-miny)/(maxy-miny);
	h = h*2-0.5;
	if (h > 1) h = 1;
	if (h < 0) h = 0;	

	vec4 color1 = texture2D(tex1,gl_TexCoord[0].st);
	vec4 color2 = texture2D(tex2,gl_TexCoord[0].st);
	gl_FragColor = mix(color1,color2,h);
}