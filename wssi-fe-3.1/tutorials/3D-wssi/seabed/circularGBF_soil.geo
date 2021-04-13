//The resolution has been larged reduced 
//due to the size of the .msh file


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

T_s=10; P_s=1.0; //small center square
T_c=10; P_c=1.0;
T_s2c=6; P_s2c=1.05;
T_c2c=10; P_c2c=1.02;
T_c2s=4; P_c2s=1.0;


N_f=13;
N_slab=7; //number of grid points for the bottom 
n_s2f1=5; r_s2f1=1.05;
n_s2f2=5; r_s2f2=0.97;
nair=2; //number of grid points for the air
rair=1.15;
//monopile circle
Point(1) = {0, 0, -hw, 1.0};

Point(2) = {-0.7071*R1, 0.7071*R1, -hw, 1.0};
Point(3) = {0.7071*R1, 0.7071*R1, -hw, 1.0};
Point(4) = {0.7071*R1, -0.7071*R1, -hw, 1.0};
Point(5) = {-0.7071*R1,-0.7071*R1, -hw, 1.0};

//biger circle
Point(6) = {-0.7071*R2, 0.7071*R2, -hw, 1.0};
Point(7) = {0.7071*R2, 0.7071*R2, -hw, 1.0};
Point(8) = {0.7071*R2, -0.7071*R2, -hw, 1.0};
Point(9) = {-0.7071*R2,-0.7071*R2, -hw, 1.0};

Point(27) = {-0.7071*R2, 0.7071*R2, -hw, 1.0};
Point(28) = {0.7071*R2, 0.7071*R2, -hw, 1.0};
Point(29) = {0.7071*R2, -0.7071*R2, -hw, 1.0};
Point(30) = {-0.7071*R2,-0.7071*R2, -hw, 1.0};

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


Line(1) = {2, 3};
Line(2) = {3, 4};
Line(3) = {4, 5};
Line(4) = {5, 2};
Transfinite Line {1,2,3,4} = T_s Using Progression P_s;


Circle(5) = {27, 1, 28};
Circle(6) = {28, 1, 29};
Circle(7) = {29, 1, 30};
Circle(8) = {30, 1, 27};
Circle(9) = {11, 1, 12};
Circle(10) = {12, 1, 13};
Circle(11) = {13, 1, 10};
Circle(12) = {10, 1, 11};
Line(13) = {14, 15};
Line(14) = {15, 16};
Line(15) = {16, 17};
Line(16) = {17, 14};
Transfinite Line {5,6,7,8,9,10,11,12,13,14,15,16} = T_c Using Progression P_c;
Line(17) = {3, 28};
Line(18) = {4, 29};
Line(19) = {5, 30};
Line(20) = {2, 27};
Transfinite Line {17,18,19,20} = T_s2c Using Progression P_s2c;
Line(21) = {28, 11};
Line(22) = {29, 12};
Line(23) = {30, 13};
Line(24) = {27, 10};
Transfinite Line {21,22,23,24} = T_c2c Using Progression P_c2c;
Line(25) = {11, 15};
Line(26) = {12, 16};
Line(27) = {13, 17};
Line(28) = {10, 14};
Transfinite Line {25,26,27,28} = T_c2s Using Progression P_c2s;
Line Loop(29) = {4, 1, 2, 3};
Plane Surface(30) = {29};
Line Loop(31) = {5, -17, -1, 20};
Plane Surface(32) = {31};
Line Loop(33) = {17, 6, -18, -2};
Plane Surface(34) = {33};
Line Loop(35) = {3, 19, -7, -18};
Plane Surface(36) = {35};
Line Loop(37) = {20, -8, -19, 4};
Plane Surface(38) = {37};




Line Loop(39) = {24, 12, -21, -5};
Plane Surface(40) = {39};
Line Loop(41) = {6, 22, -9, -21};
Plane Surface(42) = {41};
Line Loop(43) = {7, 23, -10, -22};
Plane Surface(44) = {43};
Line Loop(45) = {23, 11, -24, -8};
Plane Surface(46) = {45};
Line Loop(47) = {28, 13, -25, -12};
Plane Surface(48) = {47};
Line Loop(49) = {25, 14, -26, -9};
Plane Surface(50) = {49};
Line Loop(51) = {10, 27, -15, -26};
Plane Surface(52) = {51};
Line Loop(53) = {27, 16, -28, -11};
Plane Surface(54) = {53};

Transfinite Surface {30,32,34,36,38, 40,42,44,46,48,50,52,54}; Recombine Surface {30,32,34,36,38, 40,42,44,46,48,50,52,54};

Extrude {0, 0, -30} {
  Surface{30,32,34,36,38, 40,42,44,46,48,50,52,54};Layers{50}; Recombine;
}

Physical Surface("structureBottom") = {30,32,34,36,38};
Physical Surface("seabed") = {40,42,44,46,48,50,52,54};
Physical Surface("sides") = {287, 313, 265, 331};
Physical Surface("bottom") = {230, 208, 186, 252, 120, 142, 164, 98, 318, 296, 274, 340};

Physical Volume("volume") = {12, 8, 4, 1, 2, 6, 10, 13, 9, 5, 3, 7, 11};
