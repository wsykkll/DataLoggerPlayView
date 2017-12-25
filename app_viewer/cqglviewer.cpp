#include "cqglviewer.h"


CQGLViewer::CQGLViewer(QWidget* parent) :
QGLViewer(parent),
m_nScreenTextX(10),
m_nScreenTextY(35),
m_qFont2DText("Ubuntu", 12)
{
	startAnimation();
}

CQGLViewer::~CQGLViewer()
{
}


void CQGLViewer::draw()
{
	m_nScreenTextX = 10;
	m_nScreenTextY = 35;

	double T1 = GetLocalTimeStampInSec();
	
	DrawVehInfo();
	//DrawCoordinatesSystem();
	DrawGrids();
	
	DrawVehicleModel();
	DrawPrescanLanes();
	DrawRawMWR();
	DrawImage();
	DrawRawRTK();
	DrawTSRInfo();
}


/*@brief draw vehicle mode;
*
* draw vehicle model;
*@return void;
*@note
*/
void CQGLViewer::DrawVehicleModel()
{
	//display vehicle model;
	if (m_stDisplayControl.bVehicleModel)
	{
		//display vehicle;
		glEnable(GL_LIGHTING);
		glPushMatrix();
		glTranslatef(-200.0, 0.0, 0.0);
		glRotatef(180.0, 0.0, 0.0, 1.0f);
		for (Lib3dsNode* p = m_p3dsFile->nodes; p != 0; p = p->next)
			Render3dsNode(p);
		glPopMatrix();
		glDisable(GL_LIGHTING);
	}
}


void CQGLViewer::DrawCoordinatesSystem()
{
	//set coordinate frame text color
	glColor4ub(255, 0, 0, 125);

	unsigned long long nTimeStamp = 0;//the latest transform msg's publish time;
	if (!g_pLCMSubscriber->m_lcmHandler.m_stCoordinatesDrawer.m_stTransformListener.GetLatestTimeStamp(nTimeStamp))
	{
		return;
	}
	//draw world coordiantes;
	if (m_stDisplayControl.bWorldCoordinate)
	{
		glPushMatrix();
		g_pLCMSubscriber->m_lcmHandler.m_stCoordinatesDrawer.GLSwitch2Coordinates(nTimeStamp, CFI_WORLD);
		this->drawAxis(300.0f);
		this->renderText(10.0, 10.0, 0.0, "World", m_qFont2DText);
		glPopMatrix();
	}
	//draw vehicle coordiantes;
	if (m_stDisplayControl.bVehicleCoordinate)
	{
		glPushMatrix();
		g_pLCMSubscriber->m_lcmHandler.m_stCoordinatesDrawer.GLSwitch2Coordinates(nTimeStamp, CFI_VEHICLE);
		this->drawAxis(250.0f);
		this->renderText(10.0, 10.0, 0.0, "Vehicle", m_qFont2DText);
		glPopMatrix();
	}
	//draw Camera coordinates;
	if (m_stDisplayControl.bCameraCoordinate)
	{
		glPushMatrix();
		g_pLCMSubscriber->m_lcmHandler.m_stCoordinatesDrawer.GLSwitch2Coordinates(nTimeStamp, CFI_MOBILEYE);
		this->renderText(10.0, 10.0, 0.0, "Camera", m_qFont2DText);
		this->drawAxis(50.0f);
		glPopMatrix();
	}
	//draw front mwr coordiantes;
	if (m_stDisplayControl.bFrontMWRCoordinate)
	{
		glPushMatrix();
		g_pLCMSubscriber->m_lcmHandler.m_stCoordinatesDrawer.GLSwitch2Coordinates(nTimeStamp, CFI_FRONT_MWR);
		this->renderText(10.0f, 10.0f, 0.0f, "FW", m_qFont2DText);
		this->drawAxis(50.0f);
		glPopMatrix();
	}
	//draw left mwr coordiantes;
	if (m_stDisplayControl.bLeftMWRCoordinate)
	{
		glPushMatrix();
		g_pLCMSubscriber->m_lcmHandler.m_stCoordinatesDrawer.GLSwitch2Coordinates(nTimeStamp, CFI_LEFT_MWR);
		this->renderText(10.0f, 10.0f, 0.0f, "LW", m_qFont2DText);
		this->drawAxis(50.0f);
		glPopMatrix();
	}

	//draw right mwr coordiantes;
	if (m_stDisplayControl.bRightMWRCoordinate)
	{
		glPushMatrix();
		g_pLCMSubscriber->m_lcmHandler.m_stCoordinatesDrawer.GLSwitch2Coordinates(nTimeStamp, CFI_RIGHT_MWR);
		this->renderText(10.0f, 10.0f, 0.0f, "RW", m_qFont2DText);
		this->drawAxis(50.0f);
		glPopMatrix();
	}
	if (m_stDisplayControl.bLineBetweenCoordinate)
	{
		g_pLCMSubscriber->m_lcmHandler.m_stCoordinatesDrawer.GLDrawLinesBetweenCoordinates();
	}
}

void CQGLViewer::DrawGrids()
{
	if (m_stDisplayControl.bSquareGrids)
	{
		glEnable(GL_BLEND);
		glColor4ub(100, 100, 100, 150);
		glLineWidth(1.0f);
		drawGrid(10000.0f, 20);

		glColor4ub(100, 100, 100, 20);
		glLineWidth(1.0f);
		drawGrid(10000.0f, 200);
		glDisable(GL_BLEND);
	}
	if (m_stDisplayControl.bRadicalGrids)
	{
		COLOR_4UB color(100, 100, 100, 150);
		glEnable(GL_BLEND);
		glColor4ub(100, 100, 100, 150);
		glLineWidth(1.0f);
		g_pLCMSubscriber->m_lcmHandler.m_stElementDrawer.DrawCircle(1000.0f, color, 1.0f);
		g_pLCMSubscriber->m_lcmHandler.m_stElementDrawer.DrawCircle(2000.0f, color, 1.0f);
		g_pLCMSubscriber->m_lcmHandler.m_stElementDrawer.DrawCircle(3000.0f, color, 1.0f);
		g_pLCMSubscriber->m_lcmHandler.m_stElementDrawer.DrawCircle(4000.0f, color, 1.0f);
		g_pLCMSubscriber->m_lcmHandler.m_stElementDrawer.DrawCircle(5000.0f, color, 1.0f);
		g_pLCMSubscriber->m_lcmHandler.m_stElementDrawer.DrawCircle(6000.0f, color, 1.0f);

		for (int i = 0; i <= 360; i += 30)
		{
			g_pLCMSubscriber->m_lcmHandler.m_stElementDrawer.DrawLine(POINT_3F(0.0f, 0.0f, 0.0f), POINT_3F(6500.0f*cos(
				i*DEGREE_TO_RADIAN), 6500.0f*sin(i*DEGREE_TO_RADIAN), 0.0f), color, 1.0f);
		}
		glDisable(GL_BLEND);
	}
}

/**@brief set help string on the help document;
*
* set help string on the help document;
*@return QString: the help info;
*@note
*/
QString CQGLViewer::helpString() const
{
	QString text("<h2>I n t e r f a c e</h2>");
	text += "A GUI can be added to a QGLViewer widget using Qt's <i>Designer</i>. Signals and slots ";
	text += "can then be connected to and from the viewer.<br><br>";
	text += "You can install the QGLViewer designer plugin to make the QGLViewer appear as a ";
	text += "standard Qt widget in the Designer's widget tabs. See installation pages for details.";
	return text;
}

/**@brief QGLViewer initialize function;
*
* QGLViewer initialize function, this function will initialize opengl;
*@return void;
*@note
*/
void CQGLViewer::init()
{
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glDisable(GL_LIGHT1);

	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_COLOR_MATERIAL);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	//load 3ds model;
	Load3dsModel();

	//initialize scene;
	InitializeScene();

	// Enable GL textures
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glEnable(GL_TEXTURE_2D);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Nice texture coordinate interpolation
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

/**@brief initialize scene;
*
* initialize the scene, including the light and camera;
*@return void;
*@note
*/
void CQGLViewer::InitializeScene()
{
	this->setSceneRadius(10000); //in cm;

	if (!m_p3dsFile)
	{
		return;
	}

	//Lights;
	GLfloat amb[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat dif[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat spe[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat pos[] = { 0.0f, 0.0f, 0.0f, 1.0f };

	int li = GL_LIGHT0;
	
	for (Lib3dsLight* l = m_p3dsFile->lights; l; l = l->next)
	{
		glEnable(li);

		glLightfv(li, GL_AMBIENT, amb);
		glLightfv(li, GL_DIFFUSE, dif);
		glLightfv(li, GL_SPECULAR, spe);

		pos[0] = l->position[0];
		pos[1] = l->position[1];
		pos[2] = l->position[2];
		glLightfv(li, GL_POSITION, pos);

		if (!l->spot_light)
		{
			continue;
		}

		pos[0] = l->spot[0] - l->position[0];
		pos[1] = l->spot[1] - l->position[1];
		pos[2] = l->spot[2] - l->position[2];
		glLightfv(li, GL_SPOT_DIRECTION, pos);
		++li;
	}


	//set camera view;
	qglviewer::Quaternion qua;
	qua.setAxisAngle(qglviewer::Vec(0.0, 0.0, 1.0), -PI / 2.0f);
	camera()->setOrientation(qua);
	camera()->setPosition(qglviewer::Vec(2000.0f, 0.0f, 10000.0f));

	//camera
	Lib3dsNode* c = lib3ds_file_node_by_name(m_p3dsFile, m_p3dsCameraName, LIB3DS_CAMERA_NODE);
	Lib3dsNode* t = lib3ds_file_node_by_name(m_p3dsFile, m_p3dsCameraName, LIB3DS_TARGET_NODE);
	if (!c || !t)
	{
		return;
	}

	camera()->setPosition(qglviewer::Vec(c->data.camera.pos));
	camera()->lookAt(qglviewer::Vec(t->data.target.pos));
}

/**@brief load 3ds vehicle model;
*
* load 3ds vehicle model from vehicle.3DS file;
*@return bool: if the file is successfully loaded, return true; else, return false;
*@note the vehicle.3DS file should be in the same directory of the app;
*/
const bool CQGLViewer::Load3dsModel()
{
	m_p3dsFile = lib3ds_file_load("vehicle.3DS");
	if (!m_p3dsFile)
	{
		return false;
	}

	if (m_p3dsFile->cameras)
	{
		m_p3dsCameraName = m_p3dsFile->cameras->name;
	}
	else
	{
		m_p3dsCameraName = NULL;
	}

	lib3ds_file_eval(m_p3dsFile, 0);

	InitializeScene();

	//  initScene();

	float min[3], max[3];
	lib3ds_file_bounding_box_of_objects(m_p3dsFile, true, true, true, min, max);
	setSceneBoundingBox(qglviewer::Vec(min), qglviewer::Vec(max));

	if (!m_p3dsFile->cameras)
	{
		camera()->showEntireScene();
	}
	else
	{
		updateGL();
		//update();
	}
	return true;
}

/**@brief render 3ds node;
*
* render 3ds node;
*@return void;
*@note
*/
void CQGLViewer::Render3dsNode(Lib3dsNode* node)
{
	for (Lib3dsNode* p = node->childs; p != 0; p = p->next)
	{
		Render3dsNode(p);
	}

	if (LIB3DS_OBJECT_NODE == node->type)
	{
		if (strcmp(node->name, "$$$DUMMY") == 0)
		{
			return;
		}

		if (!node->user.d)
		{
			Lib3dsMesh* mesh = lib3ds_file_mesh_by_name(m_p3dsFile, node->name);
			if (!mesh)
			{
				return;
			}

			node->user.d = glGenLists(1);
			glNewList(node->user.d, GL_COMPILE);

			Lib3dsVector* normalL = new Lib3dsVector[3 * mesh->faces];
			Lib3dsMatrix M;
			lib3ds_matrix_copy(M, mesh->matrix);
			lib3ds_matrix_inv(M);
			glMultMatrixf(&M[0][0]);

			lib3ds_mesh_calculate_normals(mesh, normalL);

			for (unsigned int p = 0; p < mesh->faces; ++p)
			{
				Lib3dsFace* f = &mesh->faceL[p];
				Lib3dsMaterial* mat = 0;

				if (f->material[0])
				{
					mat = lib3ds_file_material_by_name(m_p3dsFile, f->material);

					if (mat)
					{
						static GLfloat a[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
						float s;
						glMaterialfv(GL_FRONT, GL_AMBIENT, a);
						glMaterialfv(GL_FRONT, GL_DIFFUSE, mat->diffuse);
						glMaterialfv(GL_FRONT, GL_SPECULAR, mat->specular);
						s = pow(2.0f, 10.0f*mat->shininess);
						if (s>128.0f)
						{
							s = 128.0f;
						}
						glMaterialf(GL_FRONT, GL_SHININESS, s);
					}
					else
					{
						Lib3dsRgba a = { 0.2f, 0.2f, 0.2f, 1.0f };
						Lib3dsRgba d = { 0.8f, 0.8f, 0.8f, 1.0f };
						Lib3dsRgba s = { 0.0f, 0.0f, 0.0f, 1.0f };
						glMaterialfv(GL_FRONT, GL_AMBIENT, a);
						glMaterialfv(GL_FRONT, GL_DIFFUSE, d);
						glMaterialfv(GL_FRONT, GL_SPECULAR, s);
					}

					glBegin(GL_TRIANGLES);
					for (int i = 0; i<3; ++i)
					{
						glNormal3fv(normalL[3 * p + i]);
						glVertex3fv(mesh->pointL[f->points[i]].pos);
					}
					glEnd();
				}
			}

			delete[] normalL;
			glEndList();
		}

		if (node->user.d)
		{
			glPushMatrix();
			Lib3dsObjectData* d = &node->data.object;
			glMultMatrixf(&node->matrix[0][0]);
			glTranslatef(-d->pivot[0], -d->pivot[1], -d->pivot[2]);
			glCallList(node->user.d);
			glPopMatrix();
		}
	}
}

void CQGLViewer::DrawPrescanLanes()
{
	if (m_stDisplayControl.bPrescanLanes)
	{
		glPushMatrix();
		g_pLCMSubscriber->m_lcmHandler.m_stDrawPrescanLines.GLDrawPrescanLines(g_pLCMSubscriber->m_lcmHandler.m_stCoordinatesDrawer);
		glPopMatrix();
	}
	if (m_stDisplayControl.bPrescanMapLanes)
	{
		glPushMatrix();
		//g_pLCMSubscriber->m_lcmHandler.m_stDrawPrescanLines.GLDrawPrescanMapLines(g_pLCMSubscriber->m_lcmHandler.m_stCoordinatesDrawer);
		g_pLCMSubscriber->m_lcmHandler.m_stDrawPrescanLines.GLDrawMapLines(g_pLCMSubscriber->m_lcmHandler.m_stCoordinatesDrawer);
		glPopMatrix();
	}
	if (m_stDisplayControl.bPrescanPos)
	{
		//display image
		glPushMatrix();
		int nImgWidth = 0, nImgHeight = 0;
		g_pLCMSubscriber->m_lcmHandler.m_stDrawPrescanLines.GLDrawPrescanIMG(nImgWidth, nImgHeight);
		float ratio = 0.5;
		int nWidth = ratio * nImgWidth;
		int nHeight = ratio * nImgHeight;
		glEnable(GL_TEXTURE_2D);
		glColor3ub(255, 255, 255);
		startScreenCoordinatesSystem(true);
		glNormal3f(0.0, 0.0, 1.0);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 1.0);
		glVertex2f(0.0f, 0.0f);
		glTexCoord2f(1.0, 1.0);
		glVertex2f(nWidth, 0.0f);
		glTexCoord2f(1.0, 0.0);
		glVertex2f(nWidth, nHeight);
		glTexCoord2f(0.0, 0.0);
		glVertex2f(0.0f, nHeight);
		glEnd();
		stopScreenCoordinatesSystem();
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();

		//display RTK info
		float velocity = 0.0f;
		glColor3ub(0xD8, 0xBF, 0xD8);
		QStringList strList = g_pLCMSubscriber->m_lcmHandler.m_stDrawPrescanLines.GetRTKStringList(velocity);
		for (unsigned int i = 0; i < strList.size(); i++)
		{
			drawText(m_nScreenTextX, m_nScreenTextY, strList.at(i), m_qFont2DText);
			m_nScreenTextY += 20;
		}

		//char gcVelocity[8];
		//sprintf(gcVelocity, "%#06.2f", velocity);
		//glColor4ub(0x99, 0x33, 0xFF, 0xFF);
		//glEnable(GL_BLEND);
		//drawText(this->width() - 205, 40, QString(gcVelocity), QFont("Helvetica", 35));
		//drawText(this->width() - 60, 40, QString("km/h"), QFont("Helvetica", 20));
		//glDisable(GL_BLEND);
	}
}

void CQGLViewer::DrawRawMWR()
{
	if (m_stDisplayControl.bRawFrontMWR)
	{
		glPushMatrix();
		std::vector<TEXT_3D> vecText3D = g_pLCMSubscriber->m_lcmHandler.m_stMWRDrawer.GLDrawRawFrontMWRObjects(g_pLCMSubscriber->m_lcmHandler.m_stCoordinatesDrawer);
		Draw3DText(vecText3D, COLOR_4UB(255,0,255,255));
		glPopMatrix();
	}
	if (m_stDisplayControl.bRawESRNew)
	{
		glPushMatrix();
		std::vector<TEXT_3D> vecText3D = g_pLCMSubscriber->m_lcmHandler.m_stMWRDrawer.GLDrawRawESRNewObjects(g_pLCMSubscriber->m_lcmHandler.m_stCoordinatesDrawer);
		Draw3DText(vecText3D, COLOR_4UB(255, 0, 255, 255));
		glPopMatrix();
	}
	if (m_stDisplayControl.bRawESRNewUpdated)
	{
		glPushMatrix();
		std::vector<TEXT_3D> vecText3D = g_pLCMSubscriber->m_lcmHandler.m_stMWRDrawer.GLDrawRawESRNewUpdatedObjects(g_pLCMSubscriber->m_lcmHandler.m_stCoordinatesDrawer);
		Draw3DText(vecText3D, COLOR_4UB(255, 0, 255, 255));
		glPopMatrix();
	}
	if (m_stDisplayControl.bRawESRUpdated)
	{
		glPushMatrix();
		std::vector<TEXT_3D> vecText3D = g_pLCMSubscriber->m_lcmHandler.m_stMWRDrawer.GLDrawRawESRUpdatedObjects(g_pLCMSubscriber->m_lcmHandler.m_stCoordinatesDrawer);
		Draw3DText(vecText3D, COLOR_4UB(255, 0, 255, 255));
		glPopMatrix();
	}
	if (m_stDisplayControl.bRawESRCoasted)
	{
		glPushMatrix();
		std::vector<TEXT_3D> vecText3D = g_pLCMSubscriber->m_lcmHandler.m_stMWRDrawer.GLDrawRawESRCoastedObjects(g_pLCMSubscriber->m_lcmHandler.m_stCoordinatesDrawer);
		Draw3DText(vecText3D, COLOR_4UB(255, 0, 255, 255));
		glPopMatrix();
	}
	if (m_stDisplayControl.bESRACCObjects)
	{
		glPushMatrix();
		std::vector<TEXT_3D> vecText3D = g_pLCMSubscriber->m_lcmHandler.m_stMWRDrawer.GLDrawESRACCObjects(g_pLCMSubscriber->m_lcmHandler.m_stCoordinatesDrawer);
		Draw3DText(vecText3D, COLOR_4UB(255, 0, 255, 255));
		glPopMatrix();
	}
	if (m_stDisplayControl.bESRFCWObjects)
	{
		glPushMatrix();
		std::vector<TEXT_3D> vecText3D = g_pLCMSubscriber->m_lcmHandler.m_stMWRDrawer.GLDrawESRFCWObjects(g_pLCMSubscriber->m_lcmHandler.m_stCoordinatesDrawer);
		Draw3DText(vecText3D, COLOR_4UB(255, 0, 255, 255));
		glPopMatrix();
	}
	if (m_stDisplayControl.bRawLeftMWR)
	{
		glPushMatrix();
		std::vector<TEXT_3D> vecText3D = g_pLCMSubscriber->m_lcmHandler.m_stMWRDrawer.GLDrawRawSRRLeftObjects(g_pLCMSubscriber->m_lcmHandler.m_stCoordinatesDrawer);
		glPopMatrix();
	}

	if (m_stDisplayControl.bRawRightMWR)
	{
		glPushMatrix();
		std::vector<TEXT_3D> vecText3D = g_pLCMSubscriber->m_lcmHandler.m_stMWRDrawer.GLDrawRawSRRRightObjects(g_pLCMSubscriber->m_lcmHandler.m_stCoordinatesDrawer);
		glPopMatrix();
	}
}

void CQGLViewer::DrawRawRTK()
{
	float velocity = 0.0f;
	//display spatial/inertial info;
	if (m_stDisplayControl.bRawINS)
	{
		glColor3ub(0xD8, 0xBF, 0xD8);
		QStringList strList = g_pLCMSubscriber->m_lcmHandler.m_stINSDrawer.GetRTKStringList(velocity);
		int i = 0;
		for (i = 0; i < strList.size(); i++)
		{
			drawText(m_nScreenTextX, m_nScreenTextY, strList.at(i), m_qFont2DText);
			m_nScreenTextY += 20;
		}
	}

	//draw velocity;
	char gcVelocity[8];
	sprintf(gcVelocity, "%#06.2f", velocity);
	glColor4ub(0x99, 0x33, 0xFF, 0xFF);
	glEnable(GL_BLEND);
	drawText(this->width() - 205, 40, QString(gcVelocity), QFont("Helvetica", 35));
	drawText(this->width() - 60, 40, QString("km/h"), QFont("Helvetica", 20));
	glDisable(GL_BLEND);

}

void CQGLViewer::Draw3DText(const std::vector<TEXT_3D>& vecText3D, COLOR_4UB color)
{
	if (vecText3D.empty())
	{
		return;
	}
	glEnable(GL_BLEND);
	glColor4ub(color.cR, color.cG, color.cB, color.cA);
	for (int i = 0; i < vecText3D.size(); i++)
	{
		this->renderText(vecText3D.data()[i].stPosition.fX,
			vecText3D.data()[i].stPosition.fY,
			vecText3D.data()[i].stPosition.fZ,
			vecText3D.data()[i].strText, m_qFont2DText);
	}
	glDisable(GL_BLEND);
}

void CQGLViewer::Draw3DText(const TEXT_3D& text3D, COLOR_4UB color)
{
	glEnable(GL_BLEND);
	glColor4ub(color.cR, color.cG, color.cB, color.cA);
	this->renderText(text3D.stPosition.fX,
		text3D.stPosition.fY,
		text3D.stPosition.fZ,
		text3D.strText, m_qFont2DText);
	glDisable(GL_BLEND);
}

void CQGLViewer::DrawImage()
{
	if (m_stDisplayControl.bRawImage)
	{
		glPushMatrix();
		int nImgWidth = 0, nImgHeight = 0;
		g_pLCMSubscriber->m_lcmHandler.m_stImgDrawer.GLDrawCameraImage(nImgWidth, nImgHeight);

		float ratio = 0.5;
		int nWidth = ratio * nImgWidth;
		int nHeight = ratio * nImgHeight;

		glEnable(GL_TEXTURE_2D);
		glColor3ub(255, 255, 255);
		startScreenCoordinatesSystem(true);
		glNormal3f(0.0, 0.0, 1.0);

		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 1.0);
		glVertex2f(0.0f, 0.0f);
		glTexCoord2f(1.0, 1.0);
		glVertex2f(nWidth, 0.0f);
		glTexCoord2f(1.0, 0.0);
		glVertex2f(nWidth, nHeight);
		glTexCoord2f(0.0, 0.0);
		glVertex2f(0.0f, nHeight);
		glEnd();

		stopScreenCoordinatesSystem();
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
	}
	if (m_stDisplayControl.bMapLanelinesMark)
	{
		glPushMatrix();
		g_pLCMSubscriber->m_lcmHandler.m_stImgDrawer.GLDrawMapMarkPoints(g_pLCMSubscriber->m_lcmHandler.m_stCoordinatesDrawer);
		glPopMatrix();
	}

	if (m_stDisplayControl.bMapLanelinesCalibrated)
	{
		glPushMatrix();
		//g_pLCMSubscriber->m_lcmHandler.m_stImgDrawer.GLDrawCalibrationLaneLines(g_pLCMSubscriber->m_lcmHandler.m_stCoordinatesDrawer);
		g_pLCMSubscriber->m_lcmHandler.m_stImgDrawer.GLDrawMap(g_pLCMSubscriber->m_lcmHandler.m_stCoordinatesDrawer);
		//g_pLCMSubscriber->m_lcmHandler.m_stImgDrawer.GLDrawLocalMap(g_pLCMSubscriber->m_lcmHandler.m_stCoordinatesDrawer);
		glPopMatrix();
	}

	if (m_stDisplayControl.bMapLanelinesProcess)
	{
		glPushMatrix();
		g_pLCMSubscriber->m_lcmHandler.m_stImgDrawer.GLDrawMapLanelineProcess(g_pLCMSubscriber->m_lcmHandler.m_stCoordinatesDrawer);
		glPopMatrix();
	}
	if (m_stDisplayControl.bDetectedLanelines)
	{
		glPushMatrix();
		g_pLCMSubscriber->m_lcmHandler.m_stImgDrawer.GLDrawMapLanelineProcessNext(g_pLCMSubscriber->m_lcmHandler.m_stCoordinatesDrawer);
		glPopMatrix();
	}
	//for test
	if (m_stDisplayControl.bLane1)
	{
		glPushMatrix();
		g_pLCMSubscriber->m_lcmHandler.m_stImgDrawer.GLDrawLane1MarkPoints(g_pLCMSubscriber->m_lcmHandler.m_stCoordinatesDrawer);
		glPopMatrix();
	}
	if (m_stDisplayControl.bLane2)
	{
		glPushMatrix();
		g_pLCMSubscriber->m_lcmHandler.m_stImgDrawer.GLDrawLane2MarkPoints(g_pLCMSubscriber->m_lcmHandler.m_stCoordinatesDrawer);
		glPopMatrix();
	}
	if (m_stDisplayControl.bLane3)
	{
		glPushMatrix();
		g_pLCMSubscriber->m_lcmHandler.m_stImgDrawer.GLDrawLane3MarkPoints(g_pLCMSubscriber->m_lcmHandler.m_stCoordinatesDrawer);
		glPopMatrix();
	}
	if (m_stDisplayControl.bLane4)
	{
		glPushMatrix();
		g_pLCMSubscriber->m_lcmHandler.m_stImgDrawer.GLDrawLane4MarkPoints(g_pLCMSubscriber->m_lcmHandler.m_stCoordinatesDrawer);
		glPopMatrix();
	}

	if (m_stDisplayControl.bMapTSR)
	{
		glPushMatrix();
		g_pLCMSubscriber->m_lcmHandler.m_stImgDrawer.GLDrawMapTSRPoints(g_pLCMSubscriber->m_lcmHandler.m_stCoordinatesDrawer);
		glPopMatrix();
	}
	if (m_stDisplayControl.bDetectedLanelines)
	{
		glPushMatrix();
		g_pLCMSubscriber->m_lcmHandler.m_stImgDrawer.GLDrawLaneMarkPoints(g_pLCMSubscriber->m_lcmHandler.m_stCoordinatesDrawer);
		glPopMatrix();
	}
}

void CQGLViewer::DrawVehInfo()
{
	if (m_stDisplayControl.bRawVCU550)
	{
		glColor3ub(0xD8, 0xBF, 0xD8);
		QStringList strList = g_pLCMSubscriber->m_lcmHandler.m_stVehInfoDrawer.GetVehInfoStringList();
		int i = 0;
		for (i = 0; i < strList.size(); i++)
		{
			drawText(m_nScreenTextX, m_nScreenTextY, strList.at(i), m_qFont2DText);
			m_nScreenTextY += 20;
		}
	}
}

void CQGLViewer::DrawTSRInfo()
{
	if (m_stDisplayControl.bDetectedTSR)
	{
		glPushMatrix();
		g_pLCMSubscriber->m_lcmHandler.m_stImgDrawer.GLDrawTSRInfo(g_pLCMSubscriber->m_lcmHandler.m_stCoordinatesDrawer);
		glPopMatrix();
	}
}