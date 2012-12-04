varying float height;
uniform sampler2D tex1;
uniform sampler2D tex2;

void main(){
	float h = height+2.0;
	if(h > 4) h = 1;
	else if (h < 0) h = 0;
	else h = h/4;

	vec4 color1 = texture2D(tex1,gl_TexCoord[0].st);
	vec4 color2 = texture2D(tex2,gl_TexCoord[0].st);
	gl_FragColor = mix(color1,color2,h);
}
