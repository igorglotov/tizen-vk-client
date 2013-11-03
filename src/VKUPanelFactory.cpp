#include "VKUPanelFactory.h"
#include "VKUTab1.h"
#include "VKUTab2.h"
#include "VKUTab3.h"
#include "AppResourceId.h"
#include "VKUContactsPanel.h"
#include "VKSettingsPanel.h"
#include "VKUSearchPanel.h"

using namespace Tizen::Ui::Scenes;


VKUPanelFactory::VKUPanelFactory(void)
{
}

VKUPanelFactory::~VKUPanelFactory(void)
{
}

Tizen::Ui::Controls::Panel*
VKUPanelFactory::CreatePanelN(const Tizen::Base::String& panelId, const Tizen::Ui::Scenes::SceneId& sceneId)
{
	SceneManager* pSceneManager = SceneManager::GetInstance();
	AppAssert(pSceneManager);
	Tizen::Ui::Controls::Panel* pNewPanel = null;

	if (panelId == IDC_PANEL_DIALOGS)
	{
		VKUTab1* pPanel = new VKUTab1();
		pPanel->Initialize();
		pSceneManager->AddSceneEventListener(sceneId, *pPanel);
		pNewPanel = pPanel;
	}
	else
	if (panelId == IDC_PANEL2)
	{
		VKUTab2* pPanel = new VKUTab2();
		pPanel->Initialize();
		pSceneManager->AddSceneEventListener(sceneId, *pPanel);
		pNewPanel = pPanel;
	}
	else
	if (panelId == IDC_PANEL3)
	{
		VKUTab3* pPanel = new VKUTab3();
		pPanel->Initialize();
		pSceneManager->AddSceneEventListener(sceneId, *pPanel);
		pNewPanel = pPanel;
	}
	else if (panelId == IDC_PANEL_CONTACTS)
	{
		VKUContactsPanel* pPanel = new VKUContactsPanel();
		pPanel->Initialize();
		pNewPanel = pPanel;
	}
	else if (panelId == IDC_PANEL_SETTINGS)
	{
		VKSettingsPanel* pPanel = new VKSettingsPanel();
		pPanel->Initialize();
		pNewPanel = pPanel;
	}
	else if (panelId == IDC_PANEL_SEARCH)
	{
		VKUSearchPanel* pPanel = new VKUSearchPanel();
		pPanel->Initialize();
		pNewPanel = pPanel;
	}



	// TODO:
	// Add your panel creation code here
	return pNewPanel;
}
