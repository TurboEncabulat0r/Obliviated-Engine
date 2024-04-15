#include "editor.h"
#include "GameObject.h"
#include "imgui/imgui.h"
#include <iostream>

namespace obvl 
{
	Editor* editor = nullptr;
	

	EditorWindow::EditorWindow()
	{

	}

	EditorWindow::~EditorWindow()
	{
	}

	void EditorWindow::Update()
	{
		ImGui::Begin(name.c_str());
		this->Draw();
		ImGui::End();
	}

	void EditorWindow::Draw()
	{
		ImGui::Text("This is a window");
	}



	class Hierarchy : public EditorWindow
	{
	public:
		Hierarchy() {
			name = "Hierarchy";
		}

		void Draw() override {
			ImGui::Text("displays all objects in the scene");
		}
	};

	class Inspector : public EditorWindow
	{
	public:
		Inspector() {
			name = "Inspector";
		}

		void Draw() {
			ImGui::Text("displays information about selected object");
		}
	};

	
	class Explorer : public EditorWindow
	{
	public:
		Explorer() {
			name = "Explorer";
			open = true;
		}

		void Draw() {
			ImGui::Text("displays all files in the project");
		}
	};



	void getAllGameobjects() {

	}

	Hierarchy* hierarchy = nullptr;
	Inspector* inspector = nullptr;
	Explorer* explorer = nullptr;

	Editor::Editor()
	{
		editor = this;
		if (hierarchy == nullptr) {
			hierarchy = new Hierarchy();
			inspector = new Inspector();
			explorer = new Explorer();
		}


		this->editorWindows.push_back(hierarchy);
		this->editorWindows.push_back(inspector);
		this->editorWindows.push_back(explorer);

		std::cout << "editor created" << std::endl;

	}

	Editor::~Editor()
	{

	}

	void Editor::DrawFull()
	{
		for (int i = 0; i < this->editorWindows.size(); i++)
		{
			if (editorWindows[i]->open)
			{
				editorWindows[i]->Update();
			}
		}
	}



	

}