xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 119;
 -3.91753;35.33421;-9.25816;,
 -0.05846;35.33421;-16.02880;,
 -0.05846;-0.15940;-16.02880;,
 -3.91753;-0.15940;-9.25816;,
 1.80487;35.33421;-14.67467;,
 -1.28240;35.33421;-9.25816;,
 -1.28240;-0.15940;-9.25816;,
 1.80487;-0.15940;-14.67467;,
 9.25816;35.33421;-18.83329;,
 9.25816;2.64147;-18.83329;,
 9.25816;35.33421;-16.91827;,
 9.25816;2.64147;-16.91827;,
 18.57478;35.33421;-16.02880;,
 18.57478;-0.15940;-16.02880;,
 16.71145;35.33421;-14.67467;,
 16.71145;-0.15940;-14.67467;,
 22.43384;35.33421;-9.25816;,
 22.43384;-0.15940;-9.25816;,
 19.79872;35.33421;-9.25816;,
 19.79872;-0.15940;-9.25816;,
 18.57478;35.33421;-2.48752;,
 18.57478;-0.15940;-2.48752;,
 16.71145;35.33421;-3.84164;,
 16.71145;-0.15940;-3.84164;,
 9.25816;35.33421;0.31697;,
 9.25816;2.64147;0.31697;,
 9.25816;35.33421;-1.59805;,
 9.25816;2.64147;-1.59805;,
 -0.05846;35.33421;-2.48752;,
 -0.05846;-0.15940;-2.48752;,
 1.80487;35.33421;-3.84164;,
 1.80487;-0.15940;-3.84164;,
 -3.91753;35.33421;-9.25816;,
 -3.91753;-0.15940;-9.25816;,
 -1.28240;35.33421;-9.25816;,
 -1.28240;-0.15940;-9.25816;,
 1.80487;35.33421;-14.67467;,
 -0.05846;35.33421;-16.02880;,
 -3.91753;-0.15940;-9.25816;,
 -0.05846;-0.15940;-16.02880;,
 1.80487;-0.15940;-14.67467;,
 -1.28240;-0.15940;-9.25816;,
 9.25816;35.33421;-16.91827;,
 9.25816;35.33421;-18.83329;,
 9.25816;2.64147;-18.83329;,
 9.25816;2.64147;-16.91827;,
 16.71145;35.33421;-14.67467;,
 18.57478;35.33421;-16.02880;,
 18.57478;-0.15940;-16.02880;,
 16.71145;-0.15940;-14.67467;,
 19.79872;35.33421;-9.25816;,
 22.43384;35.33421;-9.25816;,
 22.43384;-0.15940;-9.25816;,
 19.79872;-0.15940;-9.25816;,
 16.71145;35.33421;-3.84164;,
 18.57478;35.33421;-2.48752;,
 18.57478;-0.15940;-2.48752;,
 16.71145;-0.15940;-3.84164;,
 9.25816;35.33421;-1.59805;,
 9.25816;35.33421;0.31697;,
 9.25816;2.64147;0.31697;,
 9.25816;2.64147;-1.59805;,
 1.80487;35.33421;-3.84164;,
 -0.05846;35.33421;-2.48752;,
 -0.05846;-0.15940;-2.48752;,
 1.80487;-0.15940;-3.84164;,
 -4.23650;13.51844;-9.25816;,
 -5.21062;12.70097;-12.17864;,
 -7.88414;12.70097;-9.25816;,
 -4.23650;13.51844;-9.25816;,
 -4.23650;12.70097;-13.38835;,
 -4.23650;13.51844;-9.25816;,
 -0.11635;12.70097;-11.52272;,
 -4.23650;13.51844;-9.25816;,
 1.59028;12.70097;-9.25816;,
 -4.23650;13.51844;-9.25816;,
 -0.11635;12.70097;-6.99359;,
 -4.23650;13.51844;-9.25816;,
 -4.23650;12.70097;-5.12797;,
 -4.23650;13.51844;-9.25816;,
 -5.21062;12.70097;-6.33767;,
 -4.23650;13.51844;-9.25816;,
 -7.88414;12.70097;-9.25816;,
 -12.20762;9.88388;-14.65451;,
 -17.14766;9.88388;-9.25816;,
 -4.23650;9.88388;-16.88975;,
 4.49921;9.88388;-15.49429;,
 7.41079;12.40612;-9.25816;,
 4.65349;12.68475;-5.07377;,
 -4.23650;9.88388;-1.62656;,
 -12.20762;9.88388;-3.86180;,
 -17.14766;9.88388;-9.25816;,
 -15.86380;4.42736;-16.30883;,
 -20.61817;4.42736;-9.25816;,
 -4.23650;4.42736;-19.22932;,
 6.65410;9.20078;-17.40607;,
 10.45823;7.57670;-9.25816;,
 6.65408;7.22823;-1.11025;,
 -4.23650;4.42736;0.71300;,
 -15.86378;4.42736;-2.20748;,
 -20.61817;4.42736;-9.25816;,
 -17.14766;-0.42258;-16.88975;,
 -22.43384;-0.52719;-9.25816;,
 -4.23650;-0.33819;-20.05087;,
 7.41079;2.02563;-18.07739;,
 11.52836;3.17955;-9.25816;,
 7.41079;2.06736;-0.43892;,
 -4.23650;-0.42743;1.53455;,
 -17.14766;-0.58860;-1.62656;,
 -22.43384;-0.52719;-9.25816;,
 -15.86380;-0.47979;-16.30883;,
 -20.61817;-0.47979;-9.25816;,
 -4.23650;-0.47979;-19.22932;,
 6.65410;1.65048;-17.40607;,
 10.45823;2.66955;-9.25816;,
 6.65408;1.65048;-1.11025;,
 -4.23650;-0.47979;0.71300;,
 -15.86378;-0.47979;-2.20748;,
 -20.61817;-0.47979;-9.25816;;
 
 72;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;1,8,9,2;,
 4;10,4,7,11;,
 4;8,12,13,9;,
 4;14,10,11,15;,
 4;12,16,17,13;,
 4;18,14,15,19;,
 4;16,20,21,17;,
 4;22,18,19,23;,
 4;20,24,25,21;,
 4;26,22,23,27;,
 4;24,28,29,25;,
 4;30,26,27,31;,
 4;28,32,33,29;,
 4;34,30,31,35;,
 4;0,5,36,37;,
 4;38,39,40,41;,
 4;37,36,42,43;,
 4;39,44,45,40;,
 4;43,42,46,47;,
 4;44,48,49,45;,
 4;47,46,50,51;,
 4;48,52,53,49;,
 4;51,50,54,55;,
 4;52,56,57,53;,
 4;55,54,58,59;,
 4;56,60,61,57;,
 4;59,58,62,63;,
 4;60,64,65,61;,
 4;63,62,5,0;,
 4;64,38,41,65;,
 3;66,67,68;,
 3;69,70,67;,
 3;71,72,70;,
 3;73,74,72;,
 3;75,76,74;,
 3;77,78,76;,
 3;79,80,78;,
 3;81,82,80;,
 4;68,67,83,84;,
 4;67,70,85,83;,
 4;70,72,86,85;,
 4;72,74,87,86;,
 4;74,76,88,87;,
 4;76,78,89,88;,
 4;78,80,90,89;,
 4;80,82,91,90;,
 4;84,83,92,93;,
 4;83,85,94,92;,
 4;85,86,95,94;,
 4;86,87,96,95;,
 4;87,88,97,96;,
 4;88,89,98,97;,
 4;89,90,99,98;,
 4;90,91,100,99;,
 4;93,92,101,102;,
 4;92,94,103,101;,
 4;94,95,104,103;,
 4;95,96,105,104;,
 4;96,97,106,105;,
 4;97,98,107,106;,
 4;98,99,108,107;,
 4;99,100,109,108;,
 4;102,101,110,111;,
 4;101,103,112,110;,
 4;103,104,113,112;,
 4;104,105,114,113;,
 4;105,106,115,114;,
 4;106,107,116,115;,
 4;107,108,117,116;,
 4;108,109,118,117;;
 
 MeshMaterialList {
  1;
  72;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  67;
  -1.000000;0.000000;0.000000;,
  -0.622999;0.000000;-0.782222;,
  -0.000000;0.000000;-1.000000;,
  0.622999;0.000000;-0.782222;,
  1.000000;0.000000;0.000000;,
  0.622999;0.000000;0.782222;,
  0.000000;0.000000;1.000000;,
  -0.622999;0.000000;0.782222;,
  1.000000;0.000000;-0.000000;,
  0.622999;0.000000;0.782223;,
  0.000000;0.000000;1.000000;,
  -0.622999;0.000000;0.782223;,
  -1.000000;0.000000;0.000000;,
  -0.622999;0.000000;-0.782223;,
  -0.000000;0.000000;-1.000000;,
  0.622999;0.000000;-0.782223;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.141433;-0.987433;-0.070522;,
  0.000000;-0.989425;-0.145045;,
  -0.141433;-0.987433;-0.070522;,
  -0.141433;-0.987433;0.070522;,
  0.000000;-0.989425;0.145045;,
  0.141433;-0.987433;0.070522;,
  -0.057508;0.998345;-0.000000;,
  -0.254731;0.967012;0.000000;,
  -0.243312;0.931258;-0.271216;,
  -0.053185;0.932699;-0.356713;,
  0.152332;0.941024;-0.302108;,
  0.126042;0.988199;-0.087041;,
  0.081249;0.976336;0.200414;,
  -0.081567;0.937488;0.338324;,
  -0.243312;0.931258;0.271216;,
  -0.550139;0.835073;0.000000;,
  -0.383450;0.729601;-0.566259;,
  -0.091989;0.708637;-0.699551;,
  0.236546;0.825961;-0.511698;,
  0.430741;0.900666;-0.057128;,
  0.261783;0.825964;0.499253;,
  -0.085966;0.698045;0.710875;,
  -0.383450;0.729600;0.566259;,
  -0.738995;0.405659;-0.537891;,
  -0.516064;0.365790;-0.774516;,
  -0.104496;0.344146;-0.933083;,
  0.458951;0.507433;-0.729298;,
  0.878804;0.475304;0.042300;,
  0.520329;0.394845;0.757202;,
  -0.067564;0.315671;0.946460;,
  -0.516201;0.363453;0.775525;,
  -0.792960;0.282232;-0.539963;,
  -0.550446;0.241959;-0.799040;,
  -0.057131;0.156428;-0.986036;,
  0.578775;0.176222;-0.796219;,
  0.978551;0.205922;0.005852;,
  0.571095;0.201318;0.795815;,
  -0.055913;0.164011;0.984873;,
  -0.550372;0.237092;0.800548;,
  0.020715;-0.999541;-0.022114;,
  -0.015548;-0.997729;-0.065541;,
  0.100077;-0.980550;-0.168840;,
  0.320450;-0.936043;-0.145378;,
  0.419693;-0.907653;0.004903;,
  0.328010;-0.935207;0.133406;,
  0.119896;-0.989494;0.080787;,
  0.028152;-0.999230;-0.027341;,
  -0.739049;0.403401;0.539513;,
  -0.792640;0.277526;0.542864;;
  72;
  4;0,1,1,0;,
  4;9,8,8,9;,
  4;1,2,2,1;,
  4;10,9,9,10;,
  4;2,3,3,2;,
  4;11,10,10,11;,
  4;3,4,4,3;,
  4;12,11,11,12;,
  4;4,5,5,4;,
  4;13,12,12,13;,
  4;5,6,6,5;,
  4;14,13,13,14;,
  4;6,7,7,6;,
  4;15,14,14,15;,
  4;7,0,0,7;,
  4;8,15,15,8;,
  4;16,16,16,16;,
  4;17,18,18,17;,
  4;16,16,16,16;,
  4;18,19,19,18;,
  4;16,16,16,16;,
  4;19,20,20,19;,
  4;16,16,16,16;,
  4;20,17,17,20;,
  4;16,16,16,16;,
  4;17,21,21,17;,
  4;16,16,16,16;,
  4;21,22,22,21;,
  4;16,16,16,16;,
  4;22,23,23,22;,
  4;16,16,16,16;,
  4;23,17,17,23;,
  3;24,26,25;,
  3;24,27,26;,
  3;24,28,27;,
  3;24,29,28;,
  3;24,30,29;,
  3;24,31,30;,
  3;24,32,31;,
  3;24,25,32;,
  4;25,26,34,33;,
  4;26,27,35,34;,
  4;27,28,36,35;,
  4;28,29,37,36;,
  4;29,30,38,37;,
  4;30,31,39,38;,
  4;31,32,40,39;,
  4;32,25,33,40;,
  4;33,34,42,41;,
  4;34,35,43,42;,
  4;35,36,44,43;,
  4;36,37,45,44;,
  4;37,38,46,45;,
  4;38,39,47,46;,
  4;39,40,48,47;,
  4;40,33,65,48;,
  4;41,42,50,49;,
  4;42,43,51,50;,
  4;43,44,52,51;,
  4;44,45,53,52;,
  4;45,46,54,53;,
  4;46,47,55,54;,
  4;47,48,56,55;,
  4;48,65,66,56;,
  4;57,58,58,57;,
  4;58,59,59,58;,
  4;59,60,60,59;,
  4;60,61,61,60;,
  4;61,62,62,61;,
  4;62,63,63,62;,
  4;63,64,64,63;,
  4;64,57,57,64;;
 }
 MeshTextureCoords {
  119;
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.125000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.125000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.062500;0.000000;,
  0.125000;0.125000;,
  0.000000;0.125000;,
  0.187500;0.000000;,
  0.250000;0.125000;,
  0.312500;0.000000;,
  0.375000;0.125000;,
  0.437500;0.000000;,
  0.500000;0.125000;,
  0.562500;0.000000;,
  0.625000;0.125000;,
  0.687500;0.000000;,
  0.750000;0.125000;,
  0.812500;0.000000;,
  0.875000;0.125000;,
  0.937500;0.000000;,
  1.000000;0.125000;,
  0.125000;0.250000;,
  0.000000;0.250000;,
  0.250000;0.250000;,
  0.375000;0.250000;,
  0.500000;0.250000;,
  0.625000;0.250000;,
  0.750000;0.250000;,
  0.875000;0.250000;,
  1.000000;0.250000;,
  0.125000;0.375000;,
  0.000000;0.375000;,
  0.250000;0.375000;,
  0.375000;0.375000;,
  0.500000;0.375000;,
  0.625000;0.375000;,
  0.750000;0.375000;,
  0.875000;0.375000;,
  1.000000;0.375000;,
  0.125000;0.500000;,
  0.000000;0.500000;,
  0.250000;0.500000;,
  0.375000;0.500000;,
  0.500000;0.500000;,
  0.625000;0.500000;,
  0.750000;0.500000;,
  0.875000;0.500000;,
  1.000000;0.500000;,
  0.125000;0.625000;,
  0.000000;0.625000;,
  0.250000;0.625000;,
  0.375000;0.625000;,
  0.500000;0.625000;,
  0.625000;0.625000;,
  0.750000;0.625000;,
  0.875000;0.625000;,
  1.000000;0.625000;;
 }
}
