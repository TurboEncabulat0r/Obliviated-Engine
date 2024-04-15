#pragma once
#include <string>
#include <vector>

namespace obvl {

	class Editor;

	class EditorWindow {
	public:
		std::string name = "Window";
		bool open = true;

		EditorWindow();
		~EditorWindow();

		virtual void Draw();
		virtual void Update();
	};

	class Editor {
	public:

		std::vector<EditorWindow*> editorWindows;
		

		Editor();

		~Editor();


		void DrawFull();

	};


	extern Editor* editor;
}