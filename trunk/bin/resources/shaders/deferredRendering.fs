#version 330 core
#define DIFFUSE		0
#define POSITION	1
#define NORMAL		2
#define TEXCOORD	3
#define FRAG_COLOR	0

uniform sampler2D TEX_DIFF; 
uniform sampler2D TEX_POS;
uniform sampler2D TEX_NORM;

uniform vec3 ambient_mat[16];
uniform vec3 diffuse_mat[16];
uniform vec3 specular_mat[16];
uniform vec3 pp_t_ior_mat[16];

uniform vec3 CamPos;

in block
{
	vec2 t; //TexCoord
} Vertex;

layout(location = FRAG_COLOR, index = 0) out vec4 out_FragColor;

float compute_phong_term(in vec3 N, in vec3 L, in vec3 V, in float NdotL, in float shininess)
{
	vec3 R = reflect(N, -L);
	float term = max(clamp(dot(V,R), 0.0, 1.0), 0.0);
	term = pow(term, shininess);
	return term;
}

float compute_blinn_term(in vec3 N, in vec3 L, in vec3 V, in float NdotL, in float shininess)
{
	vec3 H = normalize(L + V);
	float term = dot(N,H);
	term = max(clamp(term, 0.0, 1.0), 0.0);
	term = pow(term, shininess);
	return term;
}

float compute_gauss_term(in vec3 N, in vec3 L, in vec3 V, in float NdotL, in float shininess)
{
	vec3 H = normalize(L+V);
	float ANH = acos(dot(N,H));
	float exponent = ANH / shininess;
	exponent = -(exponent*exponent);
	float term = max(exp(exponent), 0.0);
	return term;
}

void main( void )
{
	vec3 diffuse 	= texture( TEX_DIFF, Vertex.t ).xyz;
	vec3 position 	= texture( TEX_POS,  Vertex.t ).xyz;
	vec4 normal_matid = texture( TEX_NORM, Vertex.t );
	vec3 N = normalize(normal_matid.xyz);
	int material_id = int(normal_matid.a);
	
	vec3 light_pos = vec3(0,0,0);
	vec3 L = normalize(light_pos - position);
	vec3 V = normalize(CamPos-position);
	
	float NdotL = max(dot(N,L), 0.0);
	float shininess = pp_t_ior_mat[material_id].r;
	float term = compute_gauss_term(N, L, V, NdotL, shininess);
	
	out_FragColor = vec4( 
		((diffuse * diffuse_mat[material_id] * NdotL) +
		(specular_mat[material_id] * term) +
		(diffuse * ambient_mat[material_id])), 
		1.0
		);
		
	//out_FragColor = vec4(diffuse, 1.0);
}
