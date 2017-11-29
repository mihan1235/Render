#version 420 core
out vec4 FragColor;

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec3 Tangent;
    vec3 Bitangent;
    mat3 TBN;
    vec3 TangentLightPos;
    vec3 TangentViewPos;
    vec3 TangentFragPos;
} fs_in;

layout (binding=1) uniform sampler2D texture_diffuse1;
layout (binding=2) uniform sampler2D texture_normal1;

uniform bool normalMapping;

layout (binding=0) uniform samplerCube depthMap;
uniform float far_plane;
uniform bool shadows;
uniform vec3 lightPos;
uniform vec3 viewPos;


// array of offset direction for sampling
vec3 gridSamplingDisk[20] = vec3[]
(
   vec3(1, 1, 1), vec3(1, -1, 1), vec3(-1, -1, 1), vec3(-1, 1, 1), 
   vec3(1, 1, -1), vec3(1, -1, -1), vec3(-1, -1, -1), vec3(-1, 1, -1),
   vec3(1, 1, 0), vec3(1, -1, 0), vec3(-1, -1, 0), vec3(-1, 1, 0),
   vec3(1, 0, 1), vec3(-1, 0, 1), vec3(1, 0, -1), vec3(-1, 0, -1),
   vec3(0, 1, 1), vec3(0, -1, 1), vec3(0, -1, -1), vec3(0, 1, -1)
);


float ShadowCalculation(vec3 fragPos)
{
    // Get vector between fragment position and light position
    vec3 fragToLight = fragPos - lightPos;
    // Use the fragment to light vector to sample from the depth map    
    // float closestDepth = texture(depthMap, fragToLight).r;
    // It is currently in linear range between [0,1]. Let's re-transform it back to original depth value
    // closestDepth *= far_plane;
    // Now get current linear depth as the length between the fragment and light position
    float currentDepth = length(fragToLight);
    // Now test for shadows
    // float bias = 0.05; // We use a much larger bias since depth is now in [near_plane, far_plane] range
    // float shadow = currentDepth -  bias > closestDepth ? 1.0 : 0.0;
    // PCF
     float shadow = 0.0;
     float bias = 0.05; 
     float samples = 4.0;
     float offset = 0.1;
     for(float x = -offset; x < offset; x += offset / (samples * 0.5))
     {
         for(float y = -offset; y < offset; y += offset / (samples * 0.5))
         {
             for(float z = -offset; z < offset; z += offset / (samples * 0.5))
             {
                 float closestDepth = texture(depthMap, fragToLight + vec3(x, y, z)).r; // Use lightdir to lookup cubemap
                 closestDepth *= far_plane;   // Undo mapping [0;1]
                 if(currentDepth - bias > closestDepth)
                     shadow += 1.0;
             }
         }
     }
     shadow /= (samples * samples * samples);

	/*
    float shadow = 0.0;
    float bias = 0.15;
    int samples = 20;
    float viewDistance = length(viewPos - fragPos);
    float diskRadius = (1.0 + (viewDistance / far_plane)) / 25.0;
    for(int i = 0; i < samples; ++i)
    {
        float closestDepth = texture(depthMap, fragToLight + gridSamplingDisk[i] * diskRadius).r;
        closestDepth *= far_plane;   // Undo mapping [0;1]
        if(currentDepth - bias > closestDepth)
            shadow += 1.0;
    }
    shadow /= float(samples);
    */

    // Display closestDepth as debug (to visualize depth cubemap)
    //FragColor = vec4(vec3(closestDepth / far_plane), 1.0);    
        
    // return shadow;
    return shadow;
}

vec4 calculate_light(){
	vec3 color = texture(texture_diffuse1, fs_in.TexCoords).rgb;
    vec3 normal = normalize(fs_in.Normal);
    vec3 lightColor = vec3(0.2);
    // Ambient
    vec3 ambient = 0.1 * color;
    // Diffuse
    vec3 lightDir = normalize(lightPos - fs_in.FragPos);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * color;
    // Specular
    vec3 viewDir = normalize(viewPos - fs_in.FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = 0.0;
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);
    vec3 specular = spec * lightColor;
	// Calculate shadow
	float shadow = shadows ? ShadowCalculation(fs_in.FragPos) : 0.0;                    
    vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular));    
    return vec4(lighting, 1.0f);
}

vec4 calculate_light_normal_map(){
	vec3 normal = fs_in.Normal;
    mat3 tbn;
    // Obtain normal from normal map in range [0,1]
    normal = texture(texture_normal1, fs_in.TexCoords).rgb;
    // Transform normal vector to range [-1,1]
    normal = normalize(normal * 2.0 - 1.0);   
    // Then transform normal in tangent space to world-space via TBN matrix
    // tbn = mat3(fs_in.Tangent, fs_in.Bitangent, fs_in.Normal); // TBN calculated in fragment shader
    // normal = normalize(tbn * normal); // This works!
    // normal = normalize(fs_in.TBN * normal); // This gives incorrect results
   
    // Get diffuse color
    vec3 color = texture(texture_diffuse1, fs_in.TexCoords).rgb;
    // Ambient
    vec3 ambient = 0.1 * color;
    // Diffuse
    vec3 lightDir = normalize(fs_in.TangentLightPos - fs_in.TangentFragPos);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * color;
    // Specular
    vec3 viewDir = normalize(fs_in.TangentViewPos - fs_in.TangentFragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    float spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);

    vec3 specular = vec3(0.2) * spec;
    //FragColor = vec4(ambient + diffuse + specular, 1.0f);

	
	// Calculate shadow
  
	float shadow = shadows ? ShadowCalculation(fs_in.FragPos) : 0.0;   
	                 
    vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular));    
    
    return vec4(lighting, 1.0f);
}

void main()
{          
	if (normalMapping==true) {
		FragColor = calculate_light_normal_map();
	}
	else{
		FragColor = calculate_light();
	}
}