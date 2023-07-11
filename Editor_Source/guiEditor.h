#pragma once
#include "Common.h"
#include "Engine.h"
#include "guiWidget.h"
#include "guiEditorObject.h"
#include "guiDebugObject.h"
#include "WGraphics.h"

namespace gui
{
	class Editor
	{
	public:
		static void Initialize();
		static void Run();

		static void Update();
		static void LateUpdate();
		static void Render();
		static void Release();

		static void DebugRender(const W::graphics::DebugMesh& _mesh);

	private:
		static std::vector<Widget*> m_vecWidgets;
		static std::vector<EditorObject*> m_vecEditorObjects;
		static std::vector<DebugObject*> m_vecDebugObjects;
	};

}

