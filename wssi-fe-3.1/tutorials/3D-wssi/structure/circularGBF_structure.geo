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
h_slab=3.0;

hw=10;
h_slab=3;
h_s2f1=3;
h_s2f2=2.5;
h_f=4.5; //freesurface
h_a=2; //air

T_s=8; P_s=1.0;
T_c=8; P_c=1.0;
T_s2c=6; P_s2c=1.01;
T_c2c=12; P_c2c=1.025;


N_f=13;
N_slab=7; //number of grid points for the bottom 

//monopile circle

Point(2) = {-0.7071*R1, 0.7071*R1, -hw, 1.0};
Point(3) = {0.7071*R1, 0.7071*R1, -hw, 1.0};
Point(4) = {0.7071*R1, -0.7071*R1, -hw, 1.0};
Point(5) = {-0.7071*R1,-0.7071*R1, -hw, 1.0};

//biger circle
Point(6) = {-0.7071*R1/2, 0.7071*R1/2, -hw, 1.0};
Point(7) = {0.7071*R1/2, 0.7071*R1/2, -hw, 1.0};
Point(8) = {0.7071*R1/2, -0.7071*R1/2, -hw, 1.0};
Point(9) = {-0.7071*R1/2,-0.7071*R1/2, -hw, 1.0};


Point(26) = {0, 0, -hw, 1.0};
Point(27) = {-0.7071*R2, 0.7071*R2, -hw, 1.0};
Point(28) = {0.7071*R2, 0.7071*R2, -hw, 1.0};
Point(29) = {0.7071*R2, -0.7071*R2, -hw, 1.0};
Point(30) = {-0.7071*R2,-0.7071*R2, -hw, 1.0};

Line(1) = {6, 7};
Line(2) = {7, 8};
Line(3) = {8, 9};
Line(4) = {9, 6};
Transfinite Line {1,2,3,4} = T_s Using Progression P_s;
/*
Circle(1) = {2, 26, 3};
Circle(2) = {3, 26, 4};
Circle(3) = {4, 26, 5};
Circle(4) = {5, 26, 2};
Circle(5) = {27, 26, 28};
Circle(6) = {28, 26, 29};
Circle(7) = {29, 26, 30};
Circle(8) = {30, 26, 27};
Transfinite Line {1,2,3,4,5,6,7,8} = T_c Using Progression P_c;
Line(9) = {26, 3};
Line(10) = {26, 2};
Line(11) = {26, 4};
Line(12) = {26, 5};
Transfinite Line {9,10,11,12} = T_02c Using Progression P_02c;
Line(13) = {3, 28};
Line(14) = {4, 29};
Line(15) = {5, 30};
Line(16) = {2, 27};
Transfinite Line {13,14,15,16} = T_c2c Using Progression P_c2c;
Line Loop(17) = {10, 1, -9};
Plane Surface(18) = {17};
Line Loop(19) = {9, 2, -11};
Plane Surface(20) = {19};
Line Loop(21) = {11, 3, -12};
Plane Surface(22) = {21};
Line Loop(23) = {10, -4, -12};
Plane Surface(24) = {23};
Line Loop(25) = {5, -13, -1, 16};
Plane Surface(26) = {25};
Line Loop(27) = {13, 6, -14, -2};
Plane Surface(28) = {27};
Line Loop(29) = {3, 15, -7, -14};
Plane Surface(30) = {29};
Line Loop(31) = {4, 16, -8, -15};
Plane Surface(32) = {31};
Transfinite Surface {18,20,22,24,26,28,30,32}; Recombine Surface {18,20,22,24,26,28,30,32};




Extrude {0, 0, h_slub} {
  Surface{32, 26, 28, 30, 24, 18, 20, 22};Layers{30}; Recombine;
}
Extrude {0, 0, 11.5} {
  Surface{154, 171, 188, 137};Layers{100}; Recombine;
}
Physical Surface("structureBottom") = {32, 26, 28, 30, 24, 18, 20, 22};
Physical Surface("structureTop") = {205, 239, 222, 256};
Physical Surface("slabTop") = {76, 98, 120, 54};
Physical Surface("pile") = {234, 217, 200, 251};
Physical Surface("slabSide") = {115, 89, 63, 49};
Physical Volume("volume") = {3, 2, 1, 4, 7, 6, 5, 8, 10, 9, 12, 11};

*/

Circle(5) = {2, 26, 3};
Circle(6) = {3, 26, 4};
Circle(7) = {4, 26, 5};
Circle(8) = {5, 26, 2};
Transfinite Line {5,6,7,8} = T_c Using Progression P_c;
Line(9) = {6, 2};
Line(10) = {7, 3};
Line(11) = {8, 4};
Line(12) = {9, 5};
Transfinite Line {9,10,11,12} = T_s2c Using Progression P_s2c;
Line(13) = {3, 28};
Line(14) = {4, 29};
Line(15) = {5, 30};
Line(16) = {2, 27};
Transfinite Line {13,14,15,16} = T_c2c Using Progression P_c2c;
Circle(17) = {27, 26, 28};
Circle(18) = {28, 26, 29};
Circle(19) = {29, 26, 30};
Circle(20) = {30, 26, 27};
Transfinite Line {17,18,19,20} = T_c Using Progression P_c;
Line Loop(21) = {1, 2, 3, 4};
Plane Surface(22) = {21};
Line Loop(23) = {5, -10, -1, 9};
Plane Surface(24) = {23};
Line Loop(25) = {10, 6, -11, -2};
Plane Surface(26) = {25};


Line Loop(27) = {3, 12, -7, -11};
Plane Surface(28) = {27};
Line Loop(29) = {4, 9, -8, -12};
Plane Surface(30) = {29};
Line Loop(31) = {16, 17, -13, -5};
Plane Surface(32) = {31};
Line Loop(33) = {13, 18, -14, -6};
Plane Surface(34) = {33};
Line Loop(35) = {7, 15, -19, -14};
Plane Surface(36) = {35};
Line Loop(37) = {8, 16, -20, -15};
Plane Surface(38) = {37};

Transfinite Surface {22,24,26,28,30,32,34,36,38}; Recombine Surface {22,24,26,28,30,32,34,36,38};


Extrude {0, 0, h_slab} {
  Surface{22,24,26,28,30,32,34,36,38};Layers{30}; Recombine;
}


Extrude {0, 0, 11.5} {
  Surface{148, 82, 60, 104, 126};Layers{100}; Recombine;
}


Physical Surface("structureBottom") = {22,24,26,28,30,32,34,36,38};
Physical Surface("structureTop") = {302, 258, 280, 324, 346};
Physical Surface("slabTop") = {170, 192, 214, 236};
Physical Surface("pile") = {341, 315, 253, 267};
Physical Surface("slabSide") = {231, 209, 183, 161};
Physical Volume("volume") = {3, 2, 1, 4, 7, 6, 5, 8, 10, 9, 12, 11,13,14};
