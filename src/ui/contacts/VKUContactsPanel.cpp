#include "AppResourceId.h"
#include "VKUContactsPanel.h"
#include "../../api/VKUApi.h"

using namespace Tizen::Base;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;

VKUContactsPanel::VKUContactsPanel(void) {
	pProvider = new ContactsTableProvider();
}

VKUContactsPanel::~VKUContactsPanel(void) {
	delete pProvider;
}

bool VKUContactsPanel::Initialize() {
	Panel::Construct(IDC_PANEL_CONTACTS);

	return true;
}

result VKUContactsPanel::OnInitializing(void) {
	result r = E_SUCCESS;

	Integer userIdInt = Integer(VKUAuthConfig::GetUserId());

	GroupedTableView* pTable = static_cast<GroupedTableView*>(GetControl(
			IDC_GROUPEDTABLEVIEW1));
	pTable->SetItemProvider(pProvider);

	pContactsRetrieveListener = new ContactsRetrieveListener(pTable, pProvider);

	VKUApi::GetInstance().CreateRequest("friends.get", pContactsRetrieveListener)
			->Put(L"user_id", userIdInt.ToString())
			->Put(L"fields", L"photo_100")
			->Submit();
	return r;
}

result VKUContactsPanel::OnTerminating(void) {
	result r = E_SUCCESS;

	// TODO: Add your termination code here

	return r;
}

void VKUContactsPanel::OnSceneActivatedN(
		const Tizen::Ui::Scenes::SceneId& previousSceneId,
		const Tizen::Ui::Scenes::SceneId& currentSceneId,
		Tizen::Base::Collection::IList* pArgs) {
	// TODO: Add your implementation codes here

}

void VKUContactsPanel::OnSceneDeactivated(
		const Tizen::Ui::Scenes::SceneId& currentSceneId,
		const Tizen::Ui::Scenes::SceneId& nextSceneId) {
	// TODO: Add your implementation codes here

}