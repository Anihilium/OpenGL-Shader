# **Rendering**

## *Out Line*:
pour realiser des NPR (Non-Photorealistic) la creation d'une outline est obligatoire pour un meilleur rendu <br>

**Sans outLine**<br>

pour ce faire nous utilisons les fonctions de Opengl. Ces fonctions auront pour but de *Draw* une première fois notre modèle,<br>
puis une deuxième fois mais cette fois-ci en noir <br>

dans un premier temps nous créons une variable booléenne qui se reset toutes les frames 
```
bool isOutLine = false;
```
cette variable va nous permettre de déterminer quand *Draw* l'outline<br>
c'est là qu'**OpenGL** va nous être utile, nous devons initialiser les fonctions **OpenGL** suivantes puis draw une première fois le modèle

```
glEnable(GL_CULL_FACE);

glCullFace(GL_BACK);
glDepthFunc(GL_LESS);
glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

mGraph.Update(mCam, mDirectionalLights, mPointLights, mSpotLights);
```

dans le shader nous établirons deux valeurs à envoyer 

```
uniform bool isOutLine;
uniform vec4 outLineColor;
```

et une condition en plus 
```
if(isOutLine)
        FragColor = outLineColor;
```
après avoir draw une première fois on draw une deuxieme fois mais cette fois-ci de la couleur de **l'outLine**
```
isOutLine = true;
if (isOutLine)
{
glCullFace(GL_FRONT);
glDepthFunc(GL_LEQUAL);
glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

glLineWidth(3);

mGraph.Update(mCam, mDirectionalLights, mPointLights, mSpotLights, isOutLine, Vec4(0));
}
``` 

## *Cel-Shading*:
Le Cel-Shading et le Toon-Shading aussi appelés *ombrage de celluloïd* est un modèle d'éclairage dit NPR (Non-Photorealistic).<br>
il permet de donner un aspect *cartoon* aux textures 

le Cel-Shading se base sur un principe de niveau d'ombrage, les transitions entre les zones d'ombre et de lumière sont fait brutalement. <br>
Pour ce faire nous donnons au shader une variable Level, elle permet de dire le niveau de dégradé d'ombre que nous souhaitons<br>
le calcul de la diffusion de la lumière reste le même cepandant il y a une étape en plus 

```
float CelShadingCalculation(float diff)
{
	return floor(diff * levels) / levels;
}
```
(la valeur de celshadingShininess n'est pas obligatoire mais permet un resultat plus cartoon)

```
const float celshadingShiness = 1 / levels; 
```

ce qui nous donne, appliqué aux lumières

```
vec4 DirLightCalculation(DirectionalLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(-light.direction);

    float diff = max(dot(normal, lightDir), 0.0);

    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), celshadingShiness);

    vec4 ambient = light.ambient;
    vec4 diffuse = light.diffuse * diff;
    vec4 specular = light.specular * spec;

	diffuse *= CelShadingCalculation(diff);
	ambient  *= CelShadingCalculation(diff);
	specular *= CelShadingSpecCalculation(spec);

    return (ambient + diffuse + specular);
}
```
<br>

## *Gooch-Shading*:

Le Gooch-Shading est lui aussi un NPR et a pour but de changer le système de lumières et d'ombres en couleurs chaudes et froides <br>
ce qui vas donner un aspect très coloré aux textures

pour effectuer cette effet nous modifions le calcul de l'ombrage dans le shader et nous atribuons deux couleurs <br>
une pour les teintes froides.
```
vec3(0, 0, 0.4)
```
et une autre pour les teintes chaudes
```
vec3(0.4, 0.4, 0)
```
nous créons deux float qui serviront de valeur de d'intensité pour la couleur de la texture ici *a* et *b*<br>
ce qui nous donne 

```
float a = 0.2;
float b = 0.6;

vec3 color = (1-it) * (vec3(0, 0, 0.4) + a*tex.xyz) +  it * (vec3(0.4, 0.4, 0) + b*tex.xyz);
```

puis un vecteur de réflexion à clamp pour l'envoyer ensuite à la specular (réflexion colorée)
```
float NL = dot(normalize(normal),lightDir);

vec3 R = reflect( lightDir,  normalize(normal) );
float ER = clamp( dot( normalize(viewDir), normalize(R)),0, 1);
vec4 spec = vec4(1) * pow(ER, SHININESS);
```

voici donc le calcul final à faire 
```
vec4 DirLightCalculation(DirectionalLight light, vec3 normal, vec3 viewDir, vec4 tex)
{
    float a = 0.2;
    float b = 0.6;

	vec3 lightDir = normalize(-light.direction);

    float NL = dot(normalize(normal),lightDir);

    float it = ((1 + NL) / 2);
    vec3 color = (1-it) * (vec3(0, 0, 0.4) + a*tex.xyz) +  it * (vec3(0.4, 0.4, 0) + b*tex.xyz);

    vec3 R = reflect( lightDir,  normalize(normal) );
    float ER = clamp( dot( normalize(viewDir), normalize(R)),0, 1);
    vec4 spec = vec4(1) * pow(ER, SHININESS);

    vec4 ambient = light.ambient * AMBIENT_STRENGTH;

    vec4 specular = light.specular * spec * SPECULAR_STRENGTH;

    return vec4(color + specular.xyz + ambient.xyz , tex.a);
}
```

## *Mapping*:
Nous avons mis en place des shaders de normal mapping et de parallax mapping.<br>
La logique liée aux shaders provient du site LearnOpenGL et a été légèrement adaptée, afin de prendre en compte différentes sources de lumières, par exemple.<br><br>
Pas de mapping, puis normal mapping et enfin parallax mapping (de haut en bas).<br>
Ici de loin:<br>
<img src="Screens/far.gif"><br>
Et ici de près:<br>
<img src="Screens/close.gif"><br>


## *Mappage des touches* :

**W** : avancer

**S** : reculer

**D** : aller à droite

**A** : aller à gauche

**par Kristian GOUPIL et Julien BERTRAND, GP2**
