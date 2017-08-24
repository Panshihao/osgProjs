// ***DO NOT EDIT THIS FILE - IT IS AUTOMATICALLY GENERATED BY CMAKE***

#include <osgEarthUtil/Shaders>

using namespace osgEarth::Util;

Shaders::Shaders()
{
    ContourMap_Vertex = "ContourMap.vert.glsl";
    _sources[ContourMap_Vertex] = OE_MULTILINE($__HASHTAG__version $GLSL_VERSION_STR\n
$GLSL_DEFAULT_PRECISION_FLOAT\n
\n
    // NOTE: This vertex shader is no longer used.\n
\n
$__HASHTAG__pragma vp_entryPoint oe_contour_vertex\n
$__HASHTAG__pragma vp_location   vertex_model\n
$__HASHTAG__pragma vp_order      0.5\n
\n
varying vec4 oe_layer_tilec;\n
uniform float oe_contour_min;\n
uniform float oe_contour_range;\n
varying float oe_contour_lookup;\n
\n
float oe_terrain_getElevation(in vec2 uv);\n
\n
void oe_contour_vertex(inout vec4 VertexModel)\n
{\n
    float height = oe_terrain_getElevation(oe_layer_tilec.st);\n
    float height_normalized = (height-oe_contour_min)/oe_contour_range;\n
    oe_contour_lookup = clamp( height_normalized, 0.0, 1.0 );\n
}\n
);

    ContourMap_Fragment = "ContourMap.frag.glsl";
    _sources[ContourMap_Fragment] = OE_MULTILINE($__HASHTAG__version $GLSL_VERSION_STR\n
$GLSL_DEFAULT_PRECISION_FLOAT\n
\n
$__HASHTAG__pragma vp_entryPoint oe_contour_fragment\n
$__HASHTAG__pragma vp_location   fragment_coloring\n
$__HASHTAG__pragma vp_order      0.2\n
\n
varying vec4 oe_layer_tilec;\n
uniform sampler1D oe_contour_xfer;\n
uniform float oe_contour_opacity;\n
uniform float oe_contour_min;\n
uniform float oe_contour_range;\n
\n
float oe_terrain_getElevation(in vec2 uv);\n
\n
void oe_contour_fragment( inout vec4 color )\n
{\n
    float height = oe_terrain_getElevation(oe_layer_tilec.st);\n
    float height_normalized = (height-oe_contour_min)/oe_contour_range;\n
    float lookup = clamp( height_normalized, 0.0, 1.0 );\n
    vec4 texel = texture1D( oe_contour_xfer, lookup );\n
    color.rgb = mix(color.rgb, texel.rgb, texel.a * oe_contour_opacity);\n
}\n
);

    Fog_Vertex = "Fog.vert.glsl";
    _sources[Fog_Vertex] = OE_MULTILINE($__HASHTAG__version $GLSL_VERSION_STR\n
$GLSL_DEFAULT_PRECISION_FLOAT\n
\n
$__HASHTAG__pragma vp_entryPoint oe_fog_vertex\n
$__HASHTAG__pragma vp_location   vertex_view\n
$__HASHTAG__pragma vp_order      0.5\n
\n
varying float oe_fog_fogFactor;\n
\n
void oe_fog_vertex(inout vec4 vertexVIEW)\n
{\n
    float z = length( vertexVIEW.xyz );\n
    const float LOG2 = 1.442695;\n
    oe_fog_fogFactor = exp2( -gl_Fog.density * gl_Fog.density * z * z * LOG2 );\n
    oe_fog_fogFactor = clamp(oe_fog_fogFactor, 0.0, 1.0);\n
}\n
);

    Fog_Fragment = "Fog.frag.glsl";
    _sources[Fog_Fragment] = OE_MULTILINE($__HASHTAG__version $GLSL_VERSION_STR\n
$GLSL_DEFAULT_PRECISION_FLOAT\n
\n
$__HASHTAG__pragma vp_entryPoint oe_fog_frag\n
$__HASHTAG__pragma vp_location   fragment_lighting\n
$__HASHTAG__pragma vp_order      0.7\n
\n
varying float oe_fog_fogFactor;\n
\n
void oe_fog_frag(inout vec4 color)\n
{        \n
    color.rgb = mix( gl_Fog.color.rgb, color.rgb, oe_fog_fogFactor);\n
}\n
);

    LogDepthBuffer_VertFile = "LogDepthBuffer.vert.glsl";
    _sources[LogDepthBuffer_VertFile] = OE_MULTILINE($__HASHTAG__version 110\n
\n
$__HASHTAG__pragma vp_entryPoint oe_logDepth_vert\n
$__HASHTAG__pragma vp_location   vertex_clip\n
$__HASHTAG__pragma vp_order      0.99\n
\n
uniform float oe_logDepth_FC;\n
varying float oe_logDepth_clipz;\n
\n
void oe_logDepth_vert(inout vec4 clip)\n
{\n
    if ( oe_logDepth_FC > 0.0 )\n
    {\n
        clip.z = (log2(max(1e-6, 1.0 + clip.w)) * oe_logDepth_FC - 1.0) * clip.w;\n
        oe_logDepth_clipz = 1.0 + clip.w;\n
    }\n
}\n
\n
);

    LogDepthBuffer_FragFile = "LogDepthBuffer.frag.glsl";
    _sources[LogDepthBuffer_FragFile] = OE_MULTILINE($__HASHTAG__version 110\n
\n
$__HASHTAG__pragma vp_entryPoint oe_logDepth_frag\n
$__HASHTAG__pragma vp_location   fragment_lighting\n
$__HASHTAG__pragma vp_order      0.99\n
\n
uniform float oe_logDepth_FC;\n
varying float oe_logDepth_clipz;\n
\n
void oe_logDepth_frag(inout vec4 color)\n
{\n
    if ( oe_logDepth_FC > 0.0 )\n
    {\n
        gl_FragDepth = log2(oe_logDepth_clipz) * 0.5*oe_logDepth_FC;\n
    }\n
}\n
\n
);

    LogDepthBuffer_VertOnly_VertFile = "LogDepthBuffer.VertOnly.vert.glsl";
    _sources[LogDepthBuffer_VertOnly_VertFile] = OE_MULTILINE($__HASHTAG__version 110\n
\n
$__HASHTAG__pragma vp_entryPoint oe_logDepth_vert\n
$__HASHTAG__pragma vp_location   vertex_clip\n
$__HASHTAG__pragma vp_order      0.99\n
\n
uniform float oe_logDepth_FC;\n
\n
void oe_logDepth_vert(inout vec4 clip)\n
{\n
    if ( oe_logDepth_FC > 0.0 )\n
    {\n
        clip.z = (log2(max(1e-6, clip.w+1.0))*oe_logDepth_FC - 1.0) * clip.w;\n
    }\n
}\n
\n
);

    Graticule_Fragment = "Graticule.frag.glsl";
    _sources[Graticule_Fragment] = OE_MULTILINE($__HASHTAG__version $GLSL_VERSION_STR\n
\n
$__HASHTAG__pragma vp_entryPoint oe_graticule_fragment\n
$__HASHTAG__pragma vp_location   fragment_lighting\n
$__HASHTAG__pragma vp_order      1.1\n
\n
uniform float oe_graticule_lineWidth;\n
uniform float oe_graticule_resolution;\n
uniform vec4  oe_graticule_color;\n
uniform mat4 osg_ViewMatrixInverse;\n
\n
in vec2 oe_graticule_coord;\n
\n
void oe_graticule_fragment(inout vec4 color)\n
{\n
    // double the effective res for longitude since it has twice the span\n
    vec2 gr = vec2(0.5*oe_graticule_resolution, oe_graticule_resolution);\n
    vec2 distanceToLine = mod(oe_graticule_coord, gr);\n
    vec2 dx = abs(dFdx(oe_graticule_coord));\n
    vec2 dy = abs(dFdy(oe_graticule_coord));\n
    vec2 dF = vec2(max(dx.s, dy.s), max(dx.t, dy.t)) * oe_graticule_lineWidth;\n
\n
    if ( any(lessThan(distanceToLine, dF)))\n
    {\n
        // Fade out the lines as you get closer to the ground.\n
        vec3 eye = osg_ViewMatrixInverse[3].xyz;\n
        float hae = length(eye) - 6378137.0;\n
        float maxHAE = 2000.0;\n
        float alpha = clamp(hae / maxHAE, 0.0, 1.0);\n
        color.rgb = mix(color.rgb, oe_graticule_color.rgb, oe_graticule_color.a * alpha);\n
    }\n
}\n
);

    Graticule_Vertex = "Graticule.vert.glsl";
    _sources[Graticule_Vertex] = OE_MULTILINE($__HASHTAG__version $GLSL_VERSION_STR\n
\n
$__HASHTAG__pragma vp_entryPoint oe_graticule_vertex\n
$__HASHTAG__pragma vp_location   vertex_view\n
$__HASHTAG__pragma vp_order      0.5\n
\n
uniform vec4 oe_tile_key;\n
out vec4 oe_layer_tilec;\n
out vec2 oe_graticule_coord;\n
\n
void oe_graticule_vertex(inout vec4 vertex)\n
{\n
    // calculate long and lat from [0..1] across the profile:\n
    vec2 r = (oe_tile_key.xy + oe_layer_tilec.xy)/exp2(oe_tile_key.z);\n
    oe_graticule_coord = vec2(0.5*r.x, r.y);\n
}\n
\n
);

}