//As a tutorial, the mesh density has been reduced
//compared to the simulation in the paper of Li et al. (2020)

//circular GBF
// |-----  z= 4.5 
// |       *h_a=2
// |-----  z=3
// |       *h_f=4.5
// |-----  z= -1.5       
// |       *h_s2f2=2.5   
// |_ _ _  z= -5.5
// |           *h_s2f1= 3
// |_________  z= -7 
//           | *h_slab=3
// __________| z=-10
//Parameters, all in real dimension, meter
lamda=98.2;
D=19;
R1=2.39; //radiat of the pile
R2=D/2;//radiat of the slub
h_slub=3.0;

hw=10;
h_slab=3;
h_s2f1=3;
h_s2f2=2.5;
h_f=4.5; //freesurface
h_a=2; //air


T_c=15; P_c=1.0;
T_c1c2=7; P_c1c2=1.025;
T_c2c3=9; P_c2c3=1.025;
T_c3s=3; P_c3s=1.0;
T_inlet=4; P_inlet=0.99;
T_outlet=8; P_outlet=1.01;
T_i2s=2;P_i2s=1.02;
T_s2o=2; P_s2o=1.0;

N_f=6;
N_slab=4; //number of grid points for the bottom 
n_s2f1=4; r_s2f1=1.05;
n_s2f2=4; r_s2f2=0.97;
nair=2; //number of grid points for the air
rair=1.15;
//monopile circle
Point(1) = {0, 0, -hw, 1.0};
Point(26) = {0, 0, -hw+h_slub, 1.0};
Point(2) = {-0.7071*R1, 0.7071*R1, -hw+h_slub, 1.0};
Point(3) = {0.7071*R1, 0.7071*R1, -hw+h_slub, 1.0};
Point(4) = {0.7071*R1, -0.7071*R1, -hw+h_slub, 1.0};
Point(5) = {-0.7071*R1,-0.7071*R1, -hw+h_slub, 1.0};

//biger circle
Point(6) = {-0.7071*R2, 0.7071*R2, -hw, 1.0};
Point(7) = {0.7071*R2, 0.7071*R2, -hw, 1.0};
Point(8) = {0.7071*R2, -0.7071*R2, -hw, 1.0};
Point(9) = {-0.7071*R2,-0.7071*R2, -hw, 1.0};

Point(27) = {-0.7071*R2, 0.7071*R2, -hw+h_slub, 1.0};
Point(28) = {0.7071*R2, 0.7071*R2, -hw+h_slub, 1.0};
Point(29) = {0.7071*R2, -0.7071*R2, -hw+h_slub, 1.0};
Point(30) = {-0.7071*R2,-0.7071*R2, -hw+h_slub, 1.0};

//biger biger circle
Point(10) = {-0.7071*R2*8, 0.7071*R2*8, -hw, 1.0};
Point(11) = {0.7071*R2*8, 0.7071*R2*8, -hw, 1.0};
Point(12) = {0.7071*R2*8, -0.7071*R2*8, -hw, 1.0};
Point(13) = {-0.7071*R2*8,-0.7071*R2*8, -hw, 1.0};

//square
Point(14) = {-lamda,lamda,-hw,1.0};
Point(15) = {lamda,lamda,-hw,1.0};
Point(16) = {lamda,-lamda,-hw,1.0};
Point(17) = {-lamda,-lamda,-hw,1.0};

//inlet left to right
Point(18) = {-2*lamda,lamda,-hw,1.0};
Point(19) = {-lamda-0.1*lamda,lamda,-hw,1.0};
Point(20) = {-2*lamda,-lamda,-hw,1.0};
Point(21) = {-lamda-0.1*lamda,-lamda,-hw,1.0};
//Point(18) = {-lamda-8*D-0.1*lamda,8*D,-hw,1.0};
//Point(19) = {-8*D-0.1*lamda,8*D,-hw,1.0};
//Point(20) = {-lamda-8*D-0.1*lamda,-8*D,-hw,1.0};
//Point(21) = {-8*D-0.1*lamda,-8*D,-hw,1.0};

//outlet left to right
Point(22) = {2*lamda,lamda,-hw,1.0};
Point(23) = {lamda+0.1*lamda,lamda,-hw,1.0};
Point(24) = {2*lamda,-lamda,-hw,1.0};
Point(25) = {lamda+0.1*lamda,-lamda,-hw,1.0};
//Point(22) = {lamda+8*D+0.1*lamda,8*D,-hw,1.0};
//Point(23) = {8*D+0.1*lamda,8*D,-hw,1.0};
//Point(24) = {lamda+8*D+0.1*lamda,-8*D,-hw,1.0};
//Point(25) = {8*D+0.1*lamda,-8*D,-hw,1.0};
Circle(1) = {2, 26, 3};
Circle(2) = {3, 26, 4};
Circle(3) = {4, 26, 5};
Circle(4) = {5, 26, 2};

Circle(5) = {6, 1, 7};
Circle(6) = {7, 1, 8};
Circle(7) = {8, 1, 9};
Circle(8) = {9, 1, 6};
Circle(9) = {10, 1, 11};
Circle(10) = {11, 1, 12};
Circle(11) = {12, 1, 13};
Circle(12) = {13, 1, 10};
Transfinite Line {1,2,3,4,5,6,7,8,9,10,11,12} = T_c Using Progression P_c;

Line(13) = {14, 15};
Line(14) = {15, 16};
Line(15) = {16, 17};
Line(16) = {17, 14};
Transfinite Line {13,14,15,16} = T_c Using Progression P_c;

Line(17) = {18, 19};
Line(18) = {20, 21};
Transfinite Line {17,18} = T_inlet Using Progression P_inlet;

Line(19) = {23, 22};
Line(20) = {25, 24};
Transfinite Line {19,20} = T_outlet Using Progression P_outlet;

Line(21) = {19, 14};
Line(22) = {21, 17};
Transfinite Line {21,22} = T_i2s Using Progression P_i2s;

Line(23) = {15, 23};
Line(24) = {16, 25};
Transfinite Line {23,24} = T_s2o Using Progression P_s2o;

Line(25) = {2, 27};
Line(26) = {3, 28};
Line(27) = {4, 29};
Line(28) = {5, 30};
Transfinite Line {25,26,27,28} = T_c1c2 Using Progression P_c1c2;
Line(29) = {7, 11};
Line(30) = {8, 12};
Line(31) = {9, 13};
Line(32) = {6, 10};
Transfinite Line {29,30,31,32} = T_c2c3 Using Progression P_c2c3;
Line(33) = {10, 14};
Line(34) = {11, 15};
Line(35) = {12, 16};
Line(36) = {13, 17};
Transfinite Line {33,34,35,36} = T_c3s Using Progression P_c3s;
Line(37) = {18, 20};
Line(38) = {19, 21};
Line(39) = {23, 25};
Line(40) = {22, 24};
Transfinite Line {37,38,39,40} = T_c Using Progression 1.0;

Line Loop(41) = {9, -29, -5, 32};
Plane Surface(42) = {41};
Line Loop(43) = {29, 10, -30, -6};
Plane Surface(44) = {43};
Line Loop(45) = {7, 31, -11, -30};
Plane Surface(46) = {45};
Line Loop(47) = {32, -12, -31, 8};
Plane Surface(48) = {47};
Line Loop(49) = {33, 13, -34, -9};
Plane Surface(50) = {49};
Line Loop(51) = {34, 14, -35, -10};
Plane Surface(52) = {51};
Line Loop(53) = {35, 15, -36, -11};
Plane Surface(54) = {53};
Line Loop(55) = {36, 16, -33, -12};
Plane Surface(56) = {55};
Line Loop(57) = {14, 24, -39, -23};
Plane Surface(58) = {57};
Line Loop(59) = {39, 20, -40, -19};
Plane Surface(60) = {59};
Line Loop(61) = {21, -16, -22, -38};
Plane Surface(62) = {61};
Line Loop(63) = {17, 38, -18, -37};
Plane Surface(64) = {63};
Transfinite Surface {42,44,46,48,50,52,54,56,58,60,62,64}; Recombine Surface {42,44,46,48,50,52,54,56,58,60,62,64};




//extrude the slab layer
//a = (rb - 1) / (rb^nb - 1);
//one[0] = 1;
//layer[0] = a;
//For i In {1:nb-1}
//    one[i] = 1;
//    layer[i] = layer[i-1] + a * rb^i;
//EndFor
Extrude {0, 0, h_slab} {
  Surface{64, 62, 56, 50, 52, 54, 48, 42, 44, 46, 58, 60}; Layers{N_slab};Recombine; //Layers{one[], layer[]};Recombine;
}



Line Loop(329) = {222, -25, 1, 26};
Plane Surface(330) = {329};
Line Loop(331) = {26, -245, -27, -2};
Plane Surface(332) = {331};
Line Loop(333) = {3, 28, -264, -27};
Plane Surface(334) = {333};
Line Loop(335) = {25, -201, -28, 4};
Plane Surface(336) = {335};
Transfinite Surface {330,332,334,336}; Recombine Surface {330,332,334,336};

//extrude the slab to f first part
a = (r_s2f1 - 1) / (r_s2f1^n_s2f1 - 1);
one[0] = 1;
layer[0] = a;
For i In {1:n_s2f1-1}
    one[i] = 1;
    layer[i] = layer[i-1] + a * r_s2f1^i;
EndFor
Extrude {0, 0, h_s2f1} {
  Surface{86, 108, 130, 152, 174, 196, 218, 240, 262, 284, 336, 330, 332, 334, 306, 328};Layers{one[], layer[]};Recombine;
}

//extrude the h_s2f2
as2f2 = (r_s2f2 - 1) / (r_s2f2^n_s2f2 - 1);
ones2f2[0] = 1;
layers2f2[0] = as2f2;
For i In {1:n_s2f2-1}
    ones2f2[i] = 1;
    layers2f2[i] = layers2f2[i-1] + as2f2 * r_s2f2^i;
EndFor
Extrude {0, 0, h_s2f2} {
  Surface{358, 380, 402, 424, 446, 468, 490, 512, 534, 556, 600, 622, 644, 578, 666, 688};Layers{ones2f2[], layers2f2[]};Recombine;
}


//extrude the free surface
//a = (rair - 1) / (rair^nair - 1);
//one[0] = 1;
//layer[0] = a;
//For i In {1:nair-1}
//    one[i] = 1;
//    layer[i] = layer[i-1] + a * rair^i;
//EndFor
Extrude {0, 0, h_f} {
  Surface{710, 732, 754, 776, 864, 886, 908, 842, 820, 798, 930, 952, 974, 996, 1018, 1040};Layers{N_f};Recombine;//Layers{one[], layer[]};Recombine;
}

//extrude the AIR
aAIR = (rair - 1) / (rair^nair - 1);
oneAIR[0] = 1;
layerAIR[0] = aAIR;
For i In {1:nair-1}
    oneAIR[i] = 1;
    layerAIR[i] = layerAIR[i-1] + aAIR * rair^i;
EndFor
Extrude {0, 0, h_a} {
  Surface{1062, 1084, 1106, 1128, 1260, 1238, 1216, 1150, 1172, 1194, 1282, 1304, 1348, 1326, 1370, 1392};Layers{oneAIR[], layerAIR[]};Recombine;
}

Physical Surface("seabed") = {64, 62, 56, 50, 52, 54, 48, 42, 44, 46, 58, 60};
Physical Surface("pile") = {595, 577, 631, 621, 925, 995, 961, 951,1313, 1303, 1277, 1347, 1677, 1687, 1655, 1629};
Physical Surface("atmosphere") = {1414, 1436, 1458, 1480, 1568, 1546, 1612, 1524, 1590, 1502, 1678, 1634,  1700, 1656, 1722, 1744};


Physical Surface("frontAndBack") = {1057, 705, 353, 81, 727, 375, 1079, 103, 1229, 811, 459, 187, 1361, 1009, 657, 297, 1383, 1031, 679, 319,327, 687, 1039, 1391, 305, 665, 1017, 1369, 143, 415, 767, 1119, 95, 367, 719,  1071, 73, 345, 697, 1049,1743, 1721, 1471, 1423, 1401,1409, 1431, 1515, 1713, 1735};
Physical Surface("slubSides") = {235, 261, 271, 217};
Physical Surface("outlet") = {1387, 1035, 683, 323,1739};
Physical Surface("inlet") = {85, 357, 709, 1061,1413};
Physical Surface("slubTop") = {334, 332, 330, 336};
Physical Volume("volume") = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76};




