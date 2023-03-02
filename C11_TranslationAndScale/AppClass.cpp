#include "AppClass.h"
void Application::InitVariables(void)
{
	////Change this to your name and email
	m_sProgrammer = "Alberto Bobadilla - labigm@rit.edu";
	vector3 v3Position(0.0f, 0.0f, 30.0f);
	vector3 v3Target = ZERO_V3;
	vector3 v3Upward = AXIS_Y;
	m_pCameraMngr->SetPositionTargetAndUpward(v3Position, v3Target, v3Upward);
	//init the mesh
	m_pMesh = new MyMesh();
	m_pMesh->GenerateCube(1.0f, C_BLACK);
	//m_pMesh->GenerateSphere(1.0f, 5, C_WHITE);
}
void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the arcball active?
	ArcBall();

	//Create a model matrix out of the arcball quaternion
	matrix4 m4Model = ToMatrix4(m_qArcBall);

	//Is the first person camera active?
	CameraRotation();

	//Update Entity Manager
	m_pEntityMngr->Update();

	//Add objects to render list
	m_pEntityMngr->AddEntityToRenderList(-1, true);
}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();

	matrix4 m4View = m_pCameraMngr->GetViewMatrix();
	matrix4 m4Projection = m_pCameraMngr->GetProjectionMatrix();

	matrix4 m4Scale = glm::scale(IDENTITY_M4, vector3(2.0f, 2.0f, 2.0f));
	static float value = 0.0f;
	matrix4 m4Translate = glm::translate(IDENTITY_M4, vector3(value, 2.0f, 3.0f));
	value += 0.01f;

	//matrix4 m4Model = m4Translate * m4Scale;
	matrix4 m4Model = m4Scale * m4Translate;

	//row 3
	float position = -3.0f;
	for (int i = 0; i < 7; i++)
	{
		m_pMesh->Render(m4Projection, m4View, glm::translate(m4Model, vector3(position, 0.0f, 0.0f)));
		position += 1.0f;
	}

	//row 2
	m_pMesh->Render(m4Projection, m4View, glm::translate(m4Model, vector3(-2.0f, 1.0f, 0.0f)));
	m_pMesh->Render(m4Projection, m4View, glm::translate(m4Model, vector3(2.0f, 1.0f, 0.0f)));

	//row 1
	m_pMesh->Render(m4Projection, m4View, glm::translate(m4Model, vector3(-3.0f, 2.0f, 0.0f)));
	m_pMesh->Render(m4Projection, m4View, glm::translate(m4Model, vector3(3.0f, 2.0f, 0.0f)));

	//row 4
	position = -4.0f;
	for (int i = 0; i < 9; i++)
	{
		if (i != 2 && i != 6)
		{
			m_pMesh->Render(m4Projection, m4View, glm::translate(m4Model, vector3(position, -1.0f, 0.0f)));
		}
		position += 1.0f;
	}

	//row 5
	position = -5.0f;
	for (int i = 0; i < 11; i++)
	{
		m_pMesh->Render(m4Projection, m4View, glm::translate(m4Model, vector3(position, -2.0f, 0.0f)));
		position += 1.0f;
	}

	//row 6
	position = -5.0f;
	for (int i = 0; i < 11; i++)
	{
		if (i != 1 && i != 9)
		{
			m_pMesh->Render(m4Projection, m4View, glm::translate(m4Model, vector3(position, -3.0f, 0.0f)));
		}
		position += 1.0f;
	}

	//row 7
	m_pMesh->Render(m4Projection, m4View, glm::translate(m4Model, vector3(-5.0f, -4.0f, 0.0f)));
	m_pMesh->Render(m4Projection, m4View, glm::translate(m4Model, vector3(-3.0f, -4.0f, 0.0f)));
	m_pMesh->Render(m4Projection, m4View, glm::translate(m4Model, vector3(3.0f, -4.0f, 0.0f)));
	m_pMesh->Render(m4Projection, m4View, glm::translate(m4Model, vector3(5.0f, -4.0f, 0.0f)));

	//row 8
	m_pMesh->Render(m4Projection, m4View, glm::translate(m4Model, vector3(-2.0f, -5.0f, 0.0f)));
	m_pMesh->Render(m4Projection, m4View, glm::translate(m4Model, vector3(-1.0f, -5.0f, 0.0f)));
	m_pMesh->Render(m4Projection, m4View, glm::translate(m4Model, vector3(1.0f, -5.0f, 0.0f)));
	m_pMesh->Render(m4Projection, m4View, glm::translate(m4Model, vector3(2.0f, -5.0f, 0.0f)));

	// draw a skybox
	m_pModelMngr->AddSkyboxToRenderList();

	//render list call
	m_uRenderCallCount = m_pModelMngr->Render();

	//clear the render list
	m_pModelMngr->ClearRenderList();

	//draw gui
	DrawGUI();
	
	//end the current frame (internally swaps the front and back buffers)
	m_pWindow->display();
}
void Application::Release(void)
{
	SafeDelete(m_pMesh);
	//release GUI
	ShutdownGUI();
}