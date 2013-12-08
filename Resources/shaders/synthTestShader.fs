varying vec2 v_texCoord;

uniform sampler2D CC_Texture0;
uniform float CC_alpha_value;

uniform vec2 uTexSize;

#define PI_D12 0.26179938779

void main()
{
	vec2 pixelStep = vec2(1./uTexSize.x, 1./uTexSize.y);

	//light setup	
	vec2 lightPos1 = vec2(490.*pixelStep.x, 260.*pixelStep.y);
	vec2 lightPos2 = vec2(540.*pixelStep.x, 260.*pixelStep.y);
	vec2 lightDir = vec2(0., 1.);
	
	vec4 texColor = texture2D(CC_Texture0, v_texCoord);

	if ( texColor.a > CC_alpha_value ) {
		//render
		gl_FragColor = vec4(0., 0., 0., 1.);
	} else {
		//render the void
		gl_FragColor = vec4(0., 0., 0., 0.);
		
		//light 1
		vec2 LF = normalize(v_texCoord - lightPos1);
		if(abs(acos(dot(lightDir, LF))) < PI_D12) {
			//compute occlusion
			vec2 samplePos = v_texCoord;
			bool noOcclusion = true;
			float fDotTest = 1.;
			
			while(fDotTest > 0.) {
				samplePos = samplePos + vec2(-LF.x*pixelStep.x, -LF.y*pixelStep.y);
				fDotTest = dot(lightPos1-samplePos, lightPos1-v_texCoord);
				
				vec4 texSample = texture2D(CC_Texture0, samplePos);
				if(texSample.a > CC_alpha_value && fDotTest > 0) {
					noOcclusion = false;
					break;
				}
				
			}
			
			if(noOcclusion) {
				gl_FragColor.r = 1.;
				gl_FragColor.a = 0.5;
			}
		}
		
		//light 2
		LF = normalize(v_texCoord - lightPos2);
		if(abs(acos(dot(lightDir, LF))) < PI_D12) {
			//compute occlusion
			vec2 samplePos = v_texCoord;
			bool noOcclusion = true;
			float fDotTest = 1.;
			
			while(fDotTest > 0.) {
				samplePos = samplePos + vec2(-LF.x*pixelStep.x, -LF.y*pixelStep.y);
				fDotTest = dot(lightPos2-samplePos, lightPos2-v_texCoord);
				
				vec4 texSample = texture2D(CC_Texture0, samplePos);
				if(texSample.a > CC_alpha_value && fDotTest > 0) {
					noOcclusion = false;
					break;
				}
				
			}
			
			if(noOcclusion) {
				gl_FragColor.b = 1.;
				gl_FragColor.a = 0.5;
			}
		}
	}
}
