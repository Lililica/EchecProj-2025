#version 330 core

// Attributs de sommet
in vec3 vPosition_vs; // Position du sommet transformé dans l'espace View
in vec3 vNormal_vs; // Normale du sommet transformé dans l'espace View
in vec2 vTexCoords; // Coordonnées de texture du sommet


// Matrices de transformations reçues en uniform
uniform sampler2D uTexture;
uniform vec3 uKd;
uniform vec3 uKs;
uniform float uShininess;


// Sorties du shader
out vec4 fFragColor;


void main() {
    fFragColor = texture(uTexture, vTexCoords);
}