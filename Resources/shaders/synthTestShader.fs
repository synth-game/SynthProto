varying vec2 v_texCoord;

void main()
{
	vec4 texColor = texture2D(CC_Texture0, v_texCoord);

	if ( texColor.a <= CC_alpha_value )
		gl_FragColor = vec4(1., 0., 0., 0.5);
	else
		gl_FragColor = vec4(0., 0., 0., 1.);
}
