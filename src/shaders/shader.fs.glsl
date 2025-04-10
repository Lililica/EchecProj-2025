#version 330

// Sorties du shader
in vec3 vPosition_vs; // Position du sommet transformé dans l'espace View
in vec3 vNormal_vs; // Normale du sommet transformé dans l'espace View
in vec2 vTexCoords; // Coordonnées de texture du sommet

uniform bool isTexture;
uniform vec4 uColor;
uniform sampler2D uTexture;
uniform vec3 viewPos;
uniform bool isMeteor = false;

out vec4 fFragColor;

void main() {

    if(isMeteor) {
        fFragColor = texture(uTexture, vTexCoords);
        return;
    }
    vec3 lightPos = vec3(0.0, 70.0, 0.0);
    vec3 lightColor = vec3(1.0, 0.97, 0.9);

    vec3 currentTexture = isTexture ? texture(uTexture, vTexCoords).rgb : uColor.rgb;

    vec3 Ka = vec3(1, 1, 1); // Ambient color
    vec3 Ks = vec3(0, 0, 0); // Specular color
    float Ns = 20;

    // Ambient
    vec3 ambient = Ka * (lightColor * 0.25);

    // Diffuse
    vec3 L = normalize(lightPos - vPosition_vs);
    vec3 N = normalize(vNormal_vs);
    float diff = max(dot(L, N), 0.0);
    vec3 diffuse = diff * currentTexture * lightColor;

    // Specular
    vec3 V = normalize(viewPos - vPosition_vs);
    vec3 H = normalize(L + V);
    float spec = pow(max(dot(N, H), 0.0), Ns);
    vec3 specular = spec * Ks * lightColor;

    // => Blinn-Phong
    vec3 result = ambient + diffuse + specular;
    fFragColor = vec4(result, 1.0);
}