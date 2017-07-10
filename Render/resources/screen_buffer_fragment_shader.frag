#version 420 core

in vec2 TexCoords;

out vec4 color;

layout (binding=3) uniform sampler2D screenTexture;

uniform bool effect;

void main()
{

	if (effect==true){
		///////////inverse///////////////////
		/*
		* color = vec4(vec3(1.0 - texture(screenTexture, TexCoords)), 1.0);
		*/
		/////////////////////////////////////
		///////////gray_scale////////////////
		color = texture(screenTexture, TexCoords);
		float average = (color.r + color.g + color.b) / 3.0;
		color = vec4(average, average, average, 1.0);
		/////////////////////////////////////
		//////////grey_scale_and_red/////////
		/*
		color = texture(screenTexture, TexCoords);
		float average = (color.r + color.g + color.b) / 3.0;
		color = vec4(color.r, average, average, 1.0);
		*/
		/////////////////////////////////////
	}
	else{
		///////////no_effect/////////////////
		color = texture(screenTexture, TexCoords);
		/////////////////////////////////////
	}
	

}
