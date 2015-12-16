#version 150 
//Phong Fragment Shader

in VertexData
{
//oinput position for light vector calculation
vec4 vs_Position;

//input normal vector
vec3 vs_Normals;

//input texture coordinates for fragment shader
vec2 vs_TexCoords;
} inData;

uniform bool in_hasTexture;
uniform vec4 in_ambient;
uniform vec4 in_diffuse;
uniform vec4 in_specular;
uniform float in_shininess;

uniform sampler2D tex;

uniform mat4 in_InvertedViewMat;
uniform mat4 in_LightMatrix;

struct lightSource
{
  vec4 position;
  vec4 diffuse;
  vec4 specular;
  float constantAttenuation, linearAttenuation, quadraticAttenuation;
  float spotCutoff, spotExponent;
  vec3 spotDirection;
};

lightSource light0 = lightSource(
  vec4(5.0,  1.0,  -5.0, 1.0),
  vec4(1.0,  1.0,  1.0, 1.0),
  vec4(1.0,  1.0,  1.0, 1.0),
  1.0, 0.0, 0.0,
  180.0, 0.0,
  vec3(0.0, 0.0, 0.0)
);

vec4 scene_ambient = vec4(0.2, 0.2, 0.2, 1.0);
 
struct material
{
  vec4 ambient;
  vec4 diffuse;
  vec4 specular;
  float shininess;
};
material frontMaterial = material(
  in_ambient,
  in_diffuse,
  vec4(1.0,1.0,1.0,1.0),
  5.0
);

out vec4 outColor;

void main()
{
  vec4 lightPosition = in_LightMatrix * light0.position;
  vec3 normalDirection = normalize(inData.vs_Normals);
  vec3 viewDirection = normalize(vec3(in_InvertedViewMat * vec4(0.0, 0.0, 0.0, 1.0) - inData.vs_Position));
  vec3 lightDirection;
  float attenuation;

  if (0.0 == light0.position.w) // directional light?
    {
      attenuation = 1.0; // no attenuation
      lightDirection = normalize(vec3(light0.position));
    } 
  else // point light or spotlight (or other kind of light) 
    {
      vec3 positionToLightSource = vec3(light0.position - inData.vs_Position);
      float distance = length(positionToLightSource);
      lightDirection = normalize(positionToLightSource);
      attenuation = 1.0 / (light0.constantAttenuation
                           + light0.linearAttenuation * distance
                           + light0.quadraticAttenuation * distance * distance);
 
      if (light0.spotCutoff <= 90.0) // spotlight?
	{
	  float clampedCosine = max(0.0, dot(-lightDirection, light0.spotDirection));
	  if (clampedCosine < cos(radians(light0.spotCutoff))) // outside of spotlight cone?
	    {
	      attenuation = 0.0;
	    }
	  else
	    {
	      attenuation = attenuation * pow(clampedCosine, light0.spotExponent);   
	    }
	}
  }
  if(in_hasTexture) {
	  vec4 texColor = texture(tex, inData.vs_TexCoords);
	  vec3 ambientLighting = vec3(scene_ambient) * vec3(texColor);
 
	  vec3 diffuseReflection = attenuation 
		* vec3(light0.diffuse) * vec3(texColor)
		* max(0.0, dot(normalDirection, lightDirection));
 
	  vec3 specularReflection;
	  if (dot(normalDirection, lightDirection) < 0.0) // light source on the wrong side?
		{
		  specularReflection = vec3(0.0, 0.0, 0.0); // no specular reflection
		}
	  else // light source on the right side
		{
			specularReflection = attenuation * vec3(light0.specular) * vec3(frontMaterial.specular) * (1.0 - texColor.a)
			  // for usual gloss maps: "* textureColor.a"
			* pow(max(0.0, dot(reflect(-lightDirection, normalDirection), viewDirection)), frontMaterial.shininess);
		}
	  outColor = vec4(ambientLighting + diffuseReflection + specularReflection, 1.0);
  } else {
    vec3 ambientLighting = vec3(scene_ambient) * vec3(frontMaterial.ambient);
 
	  vec3 diffuseReflection = attenuation 
		* vec3(light0.diffuse) * vec3(frontMaterial.diffuse)
		* max(0.0, dot(normalDirection, lightDirection));
 
	  vec3 specularReflection;
	  if (dot(normalDirection, lightDirection) < 0.0) // light source on the wrong side?
		{
		  specularReflection = vec3(0.0, 0.0, 0.0); // no specular reflection
		}
	  else // light source on the right side
		{
		  specularReflection = attenuation * vec3(light0.specular) * vec3(frontMaterial.specular) 
		* pow(max(0.0, dot(reflect(-lightDirection, normalDirection), viewDirection)), frontMaterial.shininess);
		}
	  outColor = vec4(ambientLighting + diffuseReflection + specularReflection, 1.0);
  }
}
