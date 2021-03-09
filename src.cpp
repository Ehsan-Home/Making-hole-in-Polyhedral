#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>
#include <iostream>
#include <vector>

using namespace std;

int zia = 0;
int hossein = 0;
//class for indexes of points 
class VertexID
{
public:
	VertexID();  //constructor

	int VertexIndex;
	int NormIndex;
private:

};
VertexID::VertexID()
{
	VertexIndex = NormIndex = 0;
}

//class for points that consists of x , y , z and it's index
class Points
{
public:
	GLdouble x;
	GLdouble y;
	GLdouble z;
	VertexID Andise;
	Points();

private:
};
Points::Points()
{
	x = y = z = Andise.VertexIndex = 0;
}


struct GLColor {
	GLfloat red;
	GLfloat green;
	GLfloat blue;
};

GLColor colors[6] = {
	{ 0.0f, 0.0f, 0.0f },	// Black
	{ 1.0f, 0.0f, 0.0f },	// Red
	{ 0.0f, 1.0f, 0.0f }, // Green
	{ 0.0f, 0.0f, 1.0f }, // Blue
	{ 1.0f, 1.0f, 0.0f }, // Yellow
	{ 1.0f, 0.0f, 1.0f }	// Purple
};

GLColor color = colors[0]; // Default: Black

						   //class for normals that consists of x , y , z and it's index
class Normals
{
public:
	GLdouble x;
	GLdouble y;
	GLdouble z;
	Normals();

private:

};
Normals::Normals()
{
	x = y = z = 0;
}


//class for face
class Face
{
public:
	int nVertex; //number of vertexes in one face
	Points * Noghte_Andis; //points of that face
	void Make_Face(int shomareamood); // for setting points on Counterclockwise side
	void Make_Face2(int shomareamood); //for making the last face (the one that connects first points (left clicked) to last points)

private:

};

//class for setting Points & Normals & Faces calsses into mesh calss that will be used for drawing
class Mesh
{
public:
	Mesh();

	int NumVertex; //Numberof all vertexes
	Points * pt;   // pointer that connects to point object
	int NumNormals; //Numberof all normals
	Normals * no;  // pointer that connects to normals object
	int NumFaces;  //numberof all faces
	Face * face;   // pointer that connects to face object

	void Draw();    //function for drawing mesh
	void makeSurfaceOfRevolution(); //function for creating mesh

private:

};
Mesh::Mesh()
{
	NumVertex = NumNormals = NumFaces = 0;
}



//objects
Points  noghat[4000];
Normals Amood[4000];
Face    Vajh[4000];
vector <int> Nexts;   //used for defining Counterclockwise movements
Mesh   mesh, mesh2;

int final_motion = 0;
GLdouble XTemp[4000];   //first left clicked points will be stored in this array , then moved to point object
GLdouble YTemp[4000];   //first left clicked points will be stored in this array , then moved to point object

bool RightClickFirstOrSeccond = 0;
int PointsNumInitialize = 0;  //number of left-clicked points 
int PointsNum = 0;            //number of all points
int MouseSelection = 0;      // 0 : left click mouse , 1 : right
int Mode = 0; // 0 for 2D , 1 for 3D
int NumVajh = 0;  //number of faces 
int Andis_Gozari_Roye_Roose_Vajh = 0; //that is used for defining points in counterclockwise way
int Andis_Gozari_Roye_Roose_Vajh2 = 0;//that is used for defining points in counterclockwise way
int teddade_davaran = 179; //number of rotates
int Shomare_Harekate_Vajh = 0; //used for moving in one face to name different vertexes
int Actions = 0; //2 : Wired frame , 3 : exit 
int CircleOrSquare = 0;//0c 1S
int CircleTurnORSqureTurn = 1; //0c 1s
int TriangleTurnORSqureTurn = 1; //0c 1s
int ClearORNotClear = 0;//0 yes 1 NO
int LetCollisonCalle = 0;
int XDumb, YDumb;
int CollisionFalg = 0;
int yplus = 0;

float r = 1.0;

int seccond_mesh = 0;
float obj_sq_x = -320;
float obj_sq_y = 320;
float objSize = 50;

float obj_sq1_x = -320;
float obj_sq1_y = 320;
float objSize1 = 50;

float obj_sq2_x = -320;
float obj_sq2_y = 320;
float objSize2 = 50;

float obj_sq3_x = -320;
float obj_sq3_y = 320;
float objSize3 = 50;

bool dragging = false;
bool dragging1 = false;
bool dragging2 = false;
bool dragging3 = false;

int draw_sq_flag = 0;
int draw_sq1_flag = 0;
int draw_Tr_flag = 0;
int draw_rec_flag = 0;
bool CheckRightButton = 0;
bool CheckRightButton2 = 0;
Points Min;



void Keyboard(unsigned char key, int mouseX, int mouseY); //keyboard selection
void Mouse(int button, int state, int x, int y);  //mouse selection
void Display(void); //for displayin
void Initialize(void); //for setting 2D or 3D views
void CoordinateDraw(void); //for drawing blue coordinates in 2D drawing
void RotateOnY(void); //for rotating points on Y
GLdouble RotateX(GLdouble x, GLdouble z); //for rotating x of points on Y
GLdouble RotateY(GLdouble y);//for rotating y of points on Y
GLdouble RotateZ(GLdouble x, GLdouble z);//for rotating z of points on Y
Normals Newvell(Face input); //determining noramls of each face on Newell method
int Number_Face_Calculate(); //for calculating faces
void PrintResult(); //for printing and testing
void mainMenuHandler(int choice);
void motion(int x, int y);
void drawRect(float x, float y, float size);
void Collision(int x, int y);
void drawCircle(float x, float y, float size);
void drawTriangle(float x, float y, float size);
void drawRect2(float x, float y, float size);




int main(int argc, char** argv)                  //Main funcion
{
	glutInit(&argc, argv);                        //Initialize the toolkit
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(640, 480);                 //Window size     = 640 * 480
	glutInitWindowPosition(100, 100);             //Window position = 100 * 100 of the total
	glutCreateWindow("EhsanGhasaei-9225003-Hw3"); //Title up the figure

	Initialize();                                 //setting 2D or 3D 

	glViewport(0, 0, 640, 480);                    //setting viewporint



	glutKeyboardFunc(Keyboard);                   //Function for checking when any keyboard is pressed
	glutDisplayFunc(Display);                     //Function for start drawing

	glutMouseFunc(Mouse);//for selecting mouse

	glutMotionFunc(motion);
	glutMainLoop();                               //Loop creator


	system("pause");
	return 0;
}

void Keyboard(unsigned char key, int mouseX, int mouseY)
{
	switch (key)
	{
	case 'A': //for giving shadow
		glutPostRedisplay();
		break;
	case 'a':  //for giving shadow
		glutPostRedisplay();
		break;
	case 'D':  //D is for default drawing , even if is not selected , that is fine
		Actions = 0; //for drawing normally
		glutPostRedisplay(); //display function is called
		break;
	case 'd':  //D is for default drawing , even if is not selected , that is fine
		Actions = 0; //for drawing normally
		glutPostRedisplay(); //display function is called
		break;
	case 'w'://W is for wired form
		Actions = 2; //for drawing form mode
		glutPostRedisplay();//display function is called
		break;
	case 'W'://W is for wired form
		Actions = 2; //for drawing form mode
		glutPostRedisplay();//display function is called
		break;
	case 'S':
		break;
	case 'E':
		exit(1); //finishing the program
		break;
	case 'e':
		exit(1); //finishing the program
		break;
	}

	return;
}

void Mouse(int button, int state, int x, int y)
{
	if (MouseSelection == 0)
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN&&final_motion == 0)
		{
			if (CheckRightButton == 0)
			{
				//cout << x << "  " << 480 - y <<endl;

				XTemp[PointsNumInitialize] = x - 320; // minusing 320 is to set to secound coordinate (blue one)
				YTemp[PointsNumInitialize] = (480 - y) - 220; // minus 480 is for finding the real position of ys
															  //minus 220 is to set to secound coordinate (blue one)

															  //cout << XTemp[PointsNumInitialize] << "   " << YTemp[PointsNumInitialize] << endl;

				PointsNumInitialize++;
			}
			else if (CheckRightButton == 1)
			{
				if (GLUT_DOWN == state)
				{
					/*if (obj_sq_x - objSize <= x && x <= obj_sq_x + objSize && obj_sq_y - objSize <= y && y <= obj_sq_y + objSize)
					{*/


					y = 480 - y;
					cout << x << "\t" << obj_sq_x - objSize << endl;
					cout << y << "\t" << obj_sq_y - objSize << endl;
					bool colliding =
						(obj_sq_x - objSize <= x) && (x <= abs(obj_sq_x + objSize))
						&&
						(obj_sq_y - objSize <= y) && (y <= obj_sq_y + objSize + 100);
					cout << colliding << endl;
					if (colliding)
					{
						dragging = true;
						obj_sq_x = x;
						obj_sq_y = y;
						glutPostRedisplay();
					}
					/*}*/

					//	if (obj_sq1_x - objSize1 <= x && x <= obj_sq1_x + objSize1 && obj_sq1_y - objSize1 <= y && y <= obj_sq1_y + objSize1)
					//{
					bool colliding1 =
						(obj_sq1_x - objSize <= x) && (x <= abs(obj_sq1_x + objSize))
						&&
						(obj_sq1_y - objSize <= y) && (y <= obj_sq1_y + objSize + 100);

					if (colliding1)
					{
						dragging1 = true;
						obj_sq1_x = x;
						obj_sq1_y = y;
						glutPostRedisplay();
					}
					//}
					bool colliding2 =
						(obj_sq2_x - objSize <= x) && (x <= abs(obj_sq2_x + objSize))
						&&
						(obj_sq2_y - objSize <= y) && (y <= obj_sq2_y + objSize + 100);

					if (colliding2)
					{
						dragging2 = true;
						obj_sq2_x = x;
						obj_sq2_y = y;
						glutPostRedisplay();
					}


					bool colliding3 =
						(obj_sq3_x - objSize <= x) && (x <= abs(obj_sq3_x + objSize))
						&&
						(obj_sq3_y - objSize <= y) && (y <= obj_sq3_y + objSize + 100);

					if (colliding3)
					{
						dragging3 = true;
						obj_sq3_x = x;
						obj_sq3_y = y;
						glutPostRedisplay();
					}

				}
				else
				{
					dragging = false;
					dragging1 = false;
					dragging2 = false;
					dragging3 = false;
				}
			}

		}
	}
	if (final_motion && state == GLUT_UP)
	{
		y = (480 - y) - 220;
		x = x - 320;
		Collision(x, y);
	}

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		if (CheckRightButton2 == 0)
		{
			MouseSelection = 0; //is for not letting the system to accept left click mouse after right click is done

			Mode = 1; // 3D
			Initialize(); // setting 3D view


			for (int i = 0; i < PointsNumInitialize; i++)
			{
				//moving points of array to point object(noghat) and setting it's z to 0 (it is on xy page)
				noghat[i].x = XTemp[i];
				noghat[i].y = YTemp[i];
				noghat[i].z = 0;
			}

			Nexts.resize(4, 0); // setting Nexts array
								//in counterclockwise side , first one is 0 , secoound one is 1 , and then is PointsNumInitialize + 1
								//finally PointsNumInitialize(this is the right way to define counterclockwise)
			Nexts[0] = 0;
			Nexts[1] = 1;
			Nexts[2] = PointsNumInitialize + 1;
			Nexts[3] = PointsNumInitialize;

			//rotates all the points
			RotateOnY();

			//finding noramls of each face and putting into amood object
			for (int i = 0; i < NumVajh; i++)
			{
				Amood[i] = Newvell(Vajh[i]);
			}

			//settin mesh
			mesh.makeSurfaceOfRevolution();
		}


		//PrintResult();

	}


	glutPostRedisplay();                                      //Function for drawing
	return;
}

void subMenuHandler(int choice)
{
	color = colors[choice];
}

void Display(void)
{
	if (ClearORNotClear == 0)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		/*cout << "ehsan" << endl;*/


	}//Clearing the window
	if (seccond_mesh)
	{
		/*cout << "Hosein" << endl;
		cout << "los : " << yplus << endl;*/
		Mode = 1;
		Initialize();
		mesh.Draw();
		glFlush();
		/*if (LetCollisonCalle == 1)
		{
		Collision(XDumb, YDumb);
		}*/
	}
	if (Mode == 0 && seccond_mesh == 0)
	{
		glPointSize(4.0); //each point : 4 pixels

		CoordinateDraw(); //drawing the coordinates

		glLineWidth(2.0);   //length of each line is 2
		glColor3f(0.0f, 0.0f, 0.0f);          //  drawing color    = black

		glBegin(GL_LINES);                    //Drawing the lines
		for (int i = 0; i < PointsNumInitialize; i++) //
		{
			if (i == PointsNumInitialize - 1)             //Skipping the last side
			{
				break;
			}
			glVertex2i(XTemp[i] + 320, YTemp[i] + 220);
			glVertex2i(XTemp[i + 1] + 320, YTemp[i + 1] + 220);
		}
		glEnd();
		glFlush(); //drawing
	}
	//if mode is greater than 0 , it is time to draw in 3D
	else if (Mode == 1 && seccond_mesh == 0)
	{
		glColor3f(0, 0, 0);
		//PrintResult();
		mesh.Draw();


		//cout << "test" << endl;

		if (draw_sq_flag)
		{
			CircleOrSquare = 1;
			drawRect(obj_sq_x, obj_sq_y, objSize);
		}
		//sq1 : circle
		if (draw_sq1_flag)
		{
			CircleOrSquare = 0;
			drawCircle(obj_sq1_x, obj_sq1_y, objSize);
		}
		//triangle
		if (draw_Tr_flag)
		{
			CircleOrSquare = 3;
			drawTriangle(obj_sq2_x, obj_sq2_y, objSize);
		}
		if (draw_rec_flag)
		{
			CircleOrSquare = 4;
			drawRect2(obj_sq3_x, obj_sq3_y, objSize);
		}


		//glutSwapBuffers();

		CheckRightButton = 1;
		CheckRightButton2 = 1;
		int subMenu = glutCreateMenu(subMenuHandler);
		glutAddMenuEntry("Default", 0);
		glutAddMenuEntry("Red", 1);
		glutAddMenuEntry("Green", 2);
		glutAddMenuEntry("Blue", 3);
		glutAddMenuEntry("Yellow", 4);
		glutAddMenuEntry("Purple", 5);

		glutCreateMenu(mainMenuHandler);

		glutAddSubMenu("Change Color", subMenu);
		glutAddMenuEntry("Square", 1);
		glutAddMenuEntry("Circle", 2);
		glutAddMenuEntry("Triangle", 3);
		glutAddMenuEntry("Rectangle", 4);
		glutAddMenuEntry("Exit", 5);

		glutAttachMenu(GLUT_RIGHT_BUTTON);
	}


	return;
}

void Initialize(void)
{
	if (Mode == 0)
	{
		//RightClickFirstOrSeccond = 0;
		glClearColor(1.0, 1.0, 1.0, 0.0); // background color = white
		glColor3f(0.0f, 0.0f, 0.0f);     //  drawing color    = black
		glPointSize(4.0);                //  point size       = 4 pixels
		glMatrixMode(GL_PROJECTION);     //setting projection matrix
		glLoadIdentity();                //matrix identity matrix
		gluOrtho2D(0.0, 640.0, 0.0, 480.0); //setting 2D volume
	}
	else
	{
		//RightClickFirstOrSeccond = 1;
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear the screen and the depth buffer 
		glLoadIdentity();//matrix identity matrix

		glMatrixMode(GL_PROJECTION);//setting projection matrix
		glLoadIdentity();//matrix identity matrix
		gluPerspective(120.0, 60.0 / 48.0, 2, -2);     //Setting Prespective mode
		glMatrixMode(GL_MODELVIEW);//setting modelview matrix
		if (zia == 0)
		{
			gluLookAt(0, 200, 300, 0, 0, 0, 0, 1, 0); //prp : (0 , 200 , 300)  eye : (0 , 0 , 0) vup : (0 , 1 , 0)
													  //gluLookAt(0, 0, 300, 0, 0, 0, 0, 1, 0); //prp : (0 , 200 , 300)  eye : (0 , 0 , 0) vup : (0 , 1 , 0)
		}
		if (zia == 1) {
			//gluLookAt(35, 335, -30, 0, 0, 0, 0, 1, 0);
			//gluLookAt(100, 10, 385, 0, 0, 0, -1, 0, -1);
			gluLookAt(0, 300, 0, 0, 0, 0, 0, 0, 1);
			//gluLookAt(0, 200, 300, 0, 0, 0, 0, 1, 0); //prp : (0 , 200 , 300)  eye : (0 , 0 , 0) vup : (0 , 1 , 0)
			//gluLookAt(0, 100, 300, 0, 0, 0, 0, 1, 0); //prp : (0 , 200 , 300)  eye : (0 , 0 , 0) vup : (0 , 1 , 0)
		}
	}


	return;
}

void CoordinateDraw()
{
	glClear(GL_COLOR_BUFFER_BIT);         //Clearing the window

	glClearColor(1.0, 1.0, 1.0, 0.0); // background color = white
	glColor3f(0.0f, 0.0f, 1.0f);     //  drawing color    = black
	glLineWidth(4.0);


	glBegin(GL_LINES);               // Y coordinate
	glVertex2i(320, 50);
	glVertex2i(320, 380);
	glEnd();
	glFlush();

	glBegin(GL_LINES);				// X coordinate
	glVertex2i(50, 220);
	glVertex2i(590, 220);
	glEnd();
	glFlush();



	return;
}

void RotateOnY(void)
{
	//measuring PointsNum that is equal to what is shown below
	PointsNum = PointsNumInitialize * (teddade_davaran + 1);

	//start rotating for x , y , z of each points
	for (int i = PointsNumInitialize; i < PointsNum; i++)
	{
		//x | y | z of each point after rotation is equal to rotate of it's same on previous points group
		noghat[i].x = RotateX(noghat[i - PointsNumInitialize].x, noghat[i - PointsNumInitialize].z);
		noghat[i].y = RotateY(noghat[i - PointsNumInitialize].y);
		noghat[i].z = RotateZ(noghat[i - PointsNumInitialize].x, noghat[i - PointsNumInitialize].z);
	}

	//calculating number of faces
	NumVajh = Number_Face_Calculate();

	//finding each point index
	for (int i = 0; i < PointsNum; i++)
	{
		noghat[i].Andise.VertexIndex = i;
	}

	////making face for all except last rotation
	//for (int i = 0; i < NumVajh - (PointsNumInitialize - 1); i++)
	//{
	//	Vajh[i].Make_Face(i);
	//}

	////finding the last side faces
	//for (int i = NumVajh - PointsNumInitialize; i < PointsNum; i++)
	//{
	//	Vajh[i].Make_Face2(i);
	//}

	//making face for all except last rotation
	for (int i = 0; i < NumVajh - 1; i++)
	{
		Vajh[i].Make_Face(i);
	}

	//finding the last side faces
	for (int i = NumVajh - 1; i < NumVajh; i++)
	{
		Vajh[i].Make_Face2(i);
	}

	return;
}

GLdouble RotateX(GLdouble x, GLdouble z)
{
	//finding that equal angle that relies on number of ratations
	int zaviye = 360 / (teddade_davaran + 1);
	//formula for rotating x
	return ((x * cos((zaviye * 3.14159265) / 180)) + (z * sin((zaviye * 3.14159265) / 180)));
}

GLdouble RotateY(GLdouble y)
{
	//stays without any changes
	return y;
}

GLdouble RotateZ(GLdouble x, GLdouble z)
{
	int zaviye = 360 / (teddade_davaran + 1);
	return ((x * -sin((zaviye * 3.14159265) / 180)) + (z * cos((zaviye * 3.14159265) / 180)));
}

Normals Newvell(Face input)
{
	//we will measure what each face will be and return it
	Normals temp;
	GLdouble num1, num2 = 0;

	//goes exactly like newvell formula (Xes) 
	for (int i = 0; i < input.nVertex; i++)
	{
		if (i == input.nVertex - 1)
		{
			num1 = (input.Noghte_Andis[i].y - input.Noghte_Andis[0].y);
			num2 = (input.Noghte_Andis[i].z + input.Noghte_Andis[0].z);
			temp.x += (num1 * num2);
		}
		else
		{
			num1 = (input.Noghte_Andis[i].y - input.Noghte_Andis[i + 1].y);
			num2 = (input.Noghte_Andis[i].z + input.Noghte_Andis[i + 1].z);
			temp.x += (num1 * num2);
		}
	}

	//goes exactly like newvell formula (Yes)
	for (int i = 0; i < input.nVertex; i++)
	{
		if (i == input.nVertex - 1)
		{
			num1 = (input.Noghte_Andis[i].z - input.Noghte_Andis[0].z);
			num2 = (input.Noghte_Andis[i].x + input.Noghte_Andis[0].x);
			temp.y += (num1 * num2);
		}
		else
		{
			num1 = (input.Noghte_Andis[i].z - input.Noghte_Andis[i + 1].z);
			num2 = (input.Noghte_Andis[i].x + input.Noghte_Andis[i + 1].x);
			temp.y += (num1 * num2);
		}
	}

	//goes exactly like newvell formula (Zes)
	for (int i = 0; i < input.nVertex; i++)
	{
		if (i == input.nVertex - 1)
		{
			num1 = (input.Noghte_Andis[i].x - input.Noghte_Andis[0].x);
			num2 = (input.Noghte_Andis[i].y + input.Noghte_Andis[0].y);
			temp.z += (num1 * num2);
		}
		else
		{
			num1 = (input.Noghte_Andis[i].x - input.Noghte_Andis[i + 1].x);
			num2 = (input.Noghte_Andis[i].y + input.Noghte_Andis[i + 1].y);
			temp.z += (num1 * num2);
		}
	}



	return temp;
}

int Number_Face_Calculate()
{
	//finding number of faces on this method
	return ((PointsNumInitialize - 1)  * (teddade_davaran + 1));
}

void Face::Make_Face(int shomareamood)
{
	this->nVertex = 4; //number of each face vertex is 4
	this->Noghte_Andis = new Points[4]; //allocating new storage for each face for it's points
	for (int i = 0; i < 4; i++)
	{
		Noghte_Andis[i] = noghat[Nexts[i] + Andis_Gozari_Roye_Roose_Vajh]; //finding each face vertex order
																		   //Andis_Gozari_Roye_Roose_Vajh is for moving between faces
		if (i == 3) //means that naming of each vertex is done and we have to go for next one
					//thus , Andis_Gozari_Roye_Roose_Vajh is increased by 1
		{
			Andis_Gozari_Roye_Roose_Vajh++;
			Shomare_Harekate_Vajh++; //for finding end of face in one group of points
			if (Shomare_Harekate_Vajh == PointsNumInitialize - 1) // it is at the end of face we have to go to next face
			{
				Andis_Gozari_Roye_Roose_Vajh++;
				Shomare_Harekate_Vajh = 0; // set to 0 to check again
			}
		}
	}

	//I found out that my method is working on clockwise waye , so simply i swapeed what is necassary
	swap(this->Noghte_Andis[0], this->Noghte_Andis[3]);
	swap(this->Noghte_Andis[1], this->Noghte_Andis[2]);

	for (int i = 0; i < this->nVertex; i++)
	{
		this->Noghte_Andis[i].Andise.NormIndex = shomareamood;
	}





	return;
}

void Face::Make_Face2(int shomareamood)
{
	//this function has set simply for each index (0 to 3)
	this->nVertex = 4;
	this->Noghte_Andis = new Points[4];
	for (int i = 0; i < 4; i++)
	{
		//if it is 0 , i have to connect first one to last one and so on
		/*if (i == 0)
		{
		this->Noghte_Andis[i] = noghat[i + (PointsNum - PointsNumInitialize) + Andis_Gozari_Roye_Roose_Vajh2];
		}
		if (i == 1)
		{
		this->Noghte_Andis[i] = noghat[i + Andis_Gozari_Roye_Roose_Vajh2];
		}
		if (i == 2)
		{
		this->Noghte_Andis[i] = noghat[i + 1 + Andis_Gozari_Roye_Roose_Vajh2];
		}
		if (i == 3)
		{
		this->Noghte_Andis[i] = noghat[i + 1 + (PointsNum - PointsNumInitialize) + Andis_Gozari_Roye_Roose_Vajh2];
		Andis_Gozari_Roye_Roose_Vajh2++;
		}*/
	}

	this->Noghte_Andis[0] = noghat[0];
	this->Noghte_Andis[1] = noghat[1];
	this->Noghte_Andis[2] = noghat[PointsNum - 1];
	this->Noghte_Andis[3] = noghat[PointsNum - 2];

	swap(this->Noghte_Andis[0], this->Noghte_Andis[3]);
	swap(this->Noghte_Andis[1], this->Noghte_Andis[2]);


	for (int i = 0; i < this->nVertex; i++)
	{
		this->Noghte_Andis[i].Andise.NormIndex = shomareamood;
	}

	return;
}

void PrintResult()
{
	/*cout << "noghat***" << endl;

	for (int i = 0; i < PointsNum; i++)
	{
	cout << noghat[i].x << "   " << noghat[i].y << "   " << noghat[i].z << endl;
	}*/


	cout << "NumVajh : " << NumVajh << endl;
	cout << "***************" << endl;
	for (int i = 0; i < NumVajh; i++)
	{
		cout << "Teddade Raas" << Vajh[i].nVertex << endl;
		for (int j = 0; j < Vajh[i].nVertex; j++)
		{
			cout << Vajh[i].Noghte_Andis[j].Andise.VertexIndex << "\t";
		}
		cout << endl << endl;
	}

	/*cout << "Amoods &&&&&" << endl;
	for (int i = 0; i < NumVajh; i++)
	{
	cout << Amood[i].x << "\t" << Amood[i].y << "\t" << Amood[i].z << endl;
	}*/


	return;
}

void Mesh::makeSurfaceOfRevolution()
{
	NumVertex = PointsNum; // setting number of vertexes
	pt = noghat;  // equaling noghat to pt 
	NumNormals = NumVajh; // setting number of normals
	no = Amood; //equaling amood to no
	NumFaces = NumVajh; // setting number of Faces 
	face = Vajh;//equaling vajh to face
	return;
}

void Mesh::Draw()
{
	//actino 0 is for when we must draw and shadow it , therefore we'll enable lightings
	if (Actions == 0)
	{
		for (int i = 0; i < NumFaces; i++)
		{
			glBegin(GL_POLYGON);
			for (int j = 0; j < face[i].nVertex; j++)
			{
				//cout << face[i].Noghte_Andis[j].Andise.NormIndex << endl;
				int in = face[i].Noghte_Andis[j].Andise.NormIndex;
				int iv = face[i].Noghte_Andis[j].Andise.VertexIndex;

				glNormal3f(no[in].x, no[in].y, no[in].z);
				glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
			}
			glEnd();
		}

		glFlush();
	}
	//actino 2 is for when we must draw wire frame , therefore we'll disable lightings
	else
	{
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear the screen and the depth buffer
		glDisable(GL_LIGHTING);
		glDisable(GL_LIGHT0);
		glDisable(GL_DEPTH_TEST);

		for (int i = 0; i < NumFaces; i++)
		{
			glBegin(GL_LINE_LOOP);
			for (int j = 0; j < face[i].nVertex; j++)
			{
				int in = face[i].Noghte_Andis[j].Andise.NormIndex;
				int iv = face[i].Noghte_Andis[j].Andise.VertexIndex;

				if (j == face[i].nVertex - 1)
				{
					break;
				}

				int iv2 = face[i].Noghte_Andis[j + 1].Andise.VertexIndex;

				glNormal3f(no[in].x, no[in].y, no[in].z);

				glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
				glVertex3f(pt[iv2].x, pt[iv2].y, pt[iv2].z);
			}
			glEnd();
		}

		glFlush();
	}
	return;
}

void mainMenuHandler(int choice)
{
	switch (choice)
	{
	case 1:	// Pixel
		draw_sq_flag = 1;
		cout << "(p)";
		glutPostRedisplay();

		break;

	case 2:	// CR
		draw_sq1_flag = 1;
		cout << "(2)";
		glutPostRedisplay();
		break;

	case 3:	// TR
		draw_Tr_flag = 1;
		cout << "(3)";
		glutPostRedisplay();
		break;

	case 4:	// reg
		draw_rec_flag = 1;
		cout << "(4)";
		glutPostRedisplay();
		break;


	case 5:	// Exitw
		exit(0);
		break;
	}
}

void motion(int x, int y)
{
	if (dragging)
	{
		obj_sq_x = -320 + x;
		//obj_sq_y = 320+y;
		obj_sq_y = 480 - y;
		//	cout << "obj_sq_y\t" << obj_sq_y << "\t y" << y << endl;
		final_motion = 1;
		glutPostRedisplay();
	}
	if (dragging1) // circle
	{
		obj_sq1_x = -320 + x;
		obj_sq1_y = 480 - y;
		final_motion = 1;
		glutPostRedisplay();
	}

	if (dragging2) // Tr
	{
		obj_sq2_x = -320 + x;
		obj_sq2_y = 480 - y;
		final_motion = 1;
		glutPostRedisplay();
	}

	if (dragging3) // Tr
	{
		obj_sq3_x = -320 + x;
		obj_sq3_y = 480 - y;
		final_motion = 1;
		glutPostRedisplay();
	}

	return;
}

void drawRect(float x, float y, float size)
{
	glPushMatrix();
	glTranslatef(x, y, 0.0f);
	glScalef(size, size, 1.0f);
	glColor3f(color.red, color.green, color.blue);
	glBegin(GL_QUADS);
	glVertex2f(-1, -1);
	glVertex2f(1, -1);
	glVertex2f(1, 1);
	glVertex2f(-1, 1);
	glEnd();
	glPopMatrix();
	glFlush();
}

void drawRect2(float x, float y, float size)
{
	glPushMatrix();
	glTranslatef(x, y, 0.0f);
	glScalef(size, size, 1.0f);
	glColor3f(color.red, color.green, color.blue);
	glBegin(GL_QUADS);
	glVertex2f(-1, -1);
	glVertex2f(3, -1);
	glVertex2f(3, 1);
	glVertex2f(-1, 1);
	glEnd();
	glPopMatrix();
	glFlush();
}

void Collision(int x, int y)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear the screen and the depth buffer 
	gluOrtho2D(0.0, 640.0, 0.0, 480.0); //setting 2D volume

	Points Min, min2;
	Min.x = Min.y = -1000;

	Points MainGin;
	Points noghte1, noghte0;

	//test
	GLdouble YMin = 1000;
	GLdouble YMax = -1000;
	for (int i = 0; i < PointsNum; i++)
	{
		if (YMin > noghat[i].y)
		{
			YMin = noghat[i].y;
		}
		if (YMax < noghat[i].y)
		{
			YMax = noghat[i].y;
		}
	}
	//end test

	/*if (obj_sq_x < 0)
	{
		obj_sq_x *= (-1);
	}*/

	for (int i = 0; i < PointsNum; i++)
	{
		if (Min.x < noghat[i].x)
		{
			Min = noghat[i];
		}
	}

	min2 = Min;
	Points MinY;
	MinY.y = -1000;

	for (int i = 0; i < PointsNum; i++)
	{
		if (MinY.y < noghat[i].y)
		{
			MinY = noghat[i];
		}
	}

	Points MinZ;
	MinZ.y = min2.y;
	MinZ.z = min2.z - 35;
	MinZ.x = min2.x - 35;

	/*noghat[0] = Min;

	noghat[1].x = obj_sq_x;
	noghat[1].y = obj_sq_y;
	noghat[1].z = 0;*/


	for (yplus = 0; yplus < 100; yplus++)
	{
		for (int i = 0; i < PointsNum; i++)
		{
			noghat[i].x = 0;
			noghat[i].y = 0;
			noghat[i].z = 0;
		}

		for (int i = 0; i < NumVajh; i++)
		{
			for (int j = 0; j < Vajh[i].nVertex; j++)
			{
				Vajh[i].Noghte_Andis[j].x = 0;
				Vajh[i].Noghte_Andis[j].y = 0;
				Vajh[i].Noghte_Andis[j].z = 0;
				Vajh[i].Noghte_Andis[j].Andise.NormIndex = 0;
				Vajh[i].Noghte_Andis[j].Andise.VertexIndex = 0;
			}
		}

		noghte0.x = Min.x;
		noghte0.y = Min.y - yplus;
		noghte0.z = Min.z;

		/*if (obj_sq_x < 50)
		{
		noghte1.x = obj_sq_x + 50;
		}
		else
		{
		noghte1.x = obj_sq_x;
		}*/
		noghte1.x = obj_sq_x;
		noghte1.y = obj_sq_y - yplus;
		noghte1.z = 0;

		/*if (CircleOrSquare == 1)
		{
			if (obj_sq_x < 50)
			{
				noghte1.x = obj_sq_x + 10;
			}
			else
			{
				noghte1.x = obj_sq_x;
			}
		}*/


		MainGin.x = (noghte0.x + noghte1.x) / 2;
		MainGin.y = (noghte0.y + noghte1.y) / 2;
		MainGin.z = (noghte0.z + noghte1.z) / 2;

		if (CircleOrSquare == 0)
		{
			glColor3f(0, 0, 0);
			noghat[0].x = Min.x;
			noghat[0].y = Min.y - yplus;
			noghat[0].z = Min.z;

			if (obj_sq_x < 20)
			{
				obj_sq_x += 50;
			}
			noghat[1].x = obj_sq_x;
			noghat[1].y = obj_sq_y - yplus;
			noghat[1].z = 0;

			teddade_davaran = 179;
		}
		else if (CircleOrSquare == 1)
		{
			if (CircleTurnORSqureTurn == 1)
			{
				if (noghte1.x < 10)
				{
					noghte1.x += 50;
					MainGin.x = (noghte0.x + noghte1.x) / 2;
					MainGin.y = (noghte0.y + noghte1.y) / 2;
					MainGin.z = (noghte0.z + noghte1.z) / 2;
				}
				glColor3f(0, 0, 0);
				ClearORNotClear = 1;
				teddade_davaran = 3;
				noghat[0] = noghte1;
				noghat[1] = MainGin;
				//LetCollisonCalle = 1;
				//				LetCollisonCalle = 1;
				if (yplus == 29)
				{
					CircleTurnORSqureTurn = 0;
					yplus = 0;
				}
			}
			else if (CircleTurnORSqureTurn == 0)
			{
				glColor3f(0, 0, 0);
				if (noghte1.x < 10)
				{
					noghte1.x += 50;
					MainGin.x = (noghte0.x + noghte1.x) / 2;
					MainGin.y = (noghte0.y + noghte1.y) / 2;
					MainGin.z = (noghte0.z + noghte1.z) / 2;
				}
				teddade_davaran = 179;
				noghat[0] = noghte1;
				noghat[1] = min2;
				//CircleTurnORSqureTurn = 1;
				ClearORNotClear = 1;

				glBegin(GL_LINES);
				for (int i = 0; i < 50; i++)
				{
					glVertex3f(noghat[0].x, noghat[0].y, noghat[0].z + i);
					glVertex3f(noghat[1].x, noghat[1].y, noghat[1].z);
				}
				glEnd();
				glFlush();

				glBegin(GL_LINES);
				for (int i = 0; i < 35; i++)
				{
					glVertex3f(min2.x, min2.y, min2.z);
					glVertex3f(noghte1.x - i, noghte1.y, noghte1.z + i);
				}
				glEnd();
				glFlush();
			}
		}
		else if (CircleOrSquare == 3)
		{
			if (TriangleTurnORSqureTurn == 1)
			{
				glColor3f(0, 0, 0);
				ClearORNotClear = 1;
				teddade_davaran = 2;
				if (noghte1.x < 10)
				{
					noghte1.x += 70;
					MainGin.x = (noghte0.x + noghte1.x) / 2;
					MainGin.y = (noghte0.y + noghte1.y) / 2;
					MainGin.z = (noghte0.z + noghte1.z) / 2;
				}
				noghat[0] = noghte1;
				noghat[1] = MainGin;
				//LetCollisonCalle = 1;
				//				LetCollisonCalle = 1;
				if (yplus == 29)
				{
					TriangleTurnORSqureTurn = 0;
					yplus = 0;
				}
			}
			else if (TriangleTurnORSqureTurn == 0)
			{
				glColor3f(0, 0, 0);
				teddade_davaran = 179;
				if (noghte1.x < 10)
				{
					noghte1.x += 70;
					MainGin.x = (noghte0.x + noghte1.x) / 2;
					MainGin.y = (noghte0.y + noghte1.y) / 2;
					MainGin.z = (noghte0.z + noghte1.z) / 2;
				}
				noghat[0] = noghte1;
				noghat[1] = min2;
				//CircleTurnORSqureTurn = 1;
				ClearORNotClear = 1;

				glBegin(GL_LINES);
				for (int i = 0; i < 50; i++)
				{
					glVertex3f(noghat[0].x, noghat[0].y, noghat[0].z + i);
					glVertex3f(noghat[1].x, noghat[1].y, noghat[1].z);
				}
				glEnd();
				glFlush();

				glBegin(GL_LINES);
				for (int i = 0; i < 35; i++)
				{
					glVertex3f(min2.x, min2.y, min2.z);
					glVertex3f(noghte1.x - i, noghte1.y, noghte1.z + i);
				}
				glEnd();
				glFlush();


			}
		}

		Andis_Gozari_Roye_Roose_Vajh = 0; //that is used for defining points in counterclockwise way
		Andis_Gozari_Roye_Roose_Vajh2 = 0;//that is used for defining points in counterclockwise way
		Shomare_Harekate_Vajh = 0; //used for moving in one face to name different vertexes

		MouseSelection = 0; //is for not letting the system to accept left click mouse after right click is done


							//Initialize();
		PointsNumInitialize = 2;
		zia = 1;

		Nexts.resize(4, 0); // setting Nexts array
							//in counterclockwise side , first one is 0 , secoound one is 1 , and then is PointsNumInitialize + 1
							//finally PointsNumInitialize(this is the right way to define counterclockwise)
		Nexts[0] = 0;
		Nexts[1] = 1;
		Nexts[2] = PointsNumInitialize + 1;
		Nexts[3] = PointsNumInitialize;

		//rotates all the points
		RotateOnY();

		//finding noramls of each face and putting into amood object
		for (int i = 0; i < NumVajh; i++)
		{
			Amood[i] = Newvell(Vajh[i]);
		}


		mesh.makeSurfaceOfRevolution();

		seccond_mesh = 1;

		Display();
	}

	return;
}

void drawCircle(float x, float y, float size)
{
	glPushMatrix();
	glTranslatef(x, y, 0.0f);
	glScalef(size, size, 1.0f);
	glColor3f(color.red, color.green, color.blue);
	int N = 360;
	float Dtheta = 2 * 3.1415926 / N;
	float angle = 0.0;
	glBegin(GL_POLYGON);
	for (int i = 0; i <= N; i++)
	{
		float angle = i*Dtheta;
		glVertex2f(r*cos(angle), r*sin(angle));
	}
	glEnd();


	glPopMatrix();
	glFlush();
}

void drawTriangle(float x, float y, float size)
{
	glPushMatrix();
	glTranslatef(x, y, 0.0f);
	glScalef(size, size, 1.0f);
	glColor3f(color.red, color.green, color.blue);
	glBegin(GL_TRIANGLES);

	glVertex3f(0, 0, 0);
	glVertex3f(3, 0, 0);
	glVertex3f(0, 2, 0);

	glEnd();



	glPopMatrix();
	glFlush();
}

