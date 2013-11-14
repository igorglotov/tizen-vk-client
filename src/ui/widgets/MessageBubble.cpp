/*
 * MessageBubble.cpp
 *
 *  Created on: Nov 7, 2013
 *      Author: igorglotov
 */

#include "MessageBubble.h"

using namespace Tizen::Graphics;
using namespace Tizen::Base;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::App;
using namespace Tizen::Base::Collection;


MessageBubble::MessageBubble() {
	result r = E_SUCCESS;
	message = null;

	AppResource* pAppResource = VKUApp::GetInstance()->GetAppResource();

	pBubbleIn = pAppResource->GetBitmapN(L"bubble_in.#.png");
	TryCatch(GetLastResult() == E_SUCCESS, r = GetLastResult(), "Failed GetBitmapN bubble_in");

	pBubbleOut = pAppResource->GetBitmapN(L"bubble_out.#.png");
	TryCatch(GetLastResult() == E_SUCCESS, r = GetLastResult(), "Failed GetBitmapN bubble_out");

	SetLastResult(r);
	return;

CATCH:
	AppLogException("$${Function:MessageBubble} is failed.", GetErrorMessage(r));
	return;
}

MessageBubble::~MessageBubble() {
	delete pBubbleIn;
	delete pBubbleOut;
}

void MessageBubble::SetOut(int out) {
	this->out = out;
}

result MessageBubble::Construct(const Tizen::Graphics::Dimension& dim) {
	result r = E_SUCCESS;
	r = itemLayout.Construct(VERTICAL_DIRECTION_UPWARD);

	placeholderLayout.Construct();
	pPlaceholderPanel = new Panel();
	pPlaceholderPanel->Construct(itemLayout, Rectangle(0, 0, dim.width, dim.height));

	TryCatch(r == E_SUCCESS, , "Failed Construct layout");

	r = Panel::Construct(placeholderLayout, Rectangle(0, 0, dim.width, dim.height), GROUP_STYLE_NONE);
	TryCatch(r == E_SUCCESS, , "Panel::Construct");

	AddControl(pPlaceholderPanel);

	pElements = new ArrayList();
	r = pElements->Construct();
	return r;

CATCH:
	AppLogException("MessageBubble::Construct is failed.", GetErrorMessage(r));
	return r;
}

result MessageBubble::AddElement(MessageElement * pElement) {
	result r = E_SUCCESS;
	Dimension mySize, elementSize;

	if (out == 1) {
		r = placeholderLayout.SetMargin(*pPlaceholderPanel, 10, 30, 10, 10);
	} else {
		r = placeholderLayout.SetMargin(*pPlaceholderPanel, 30, 10, 10, 10);
	}
	TryCatch(r == E_SUCCESS, , "Failed placeholderLayout.SetMargin");

	r = pElements->Add(pElement);
	TryCatch(r == E_SUCCESS, , "Failed pElements->Add");

	r = pPlaceholderPanel->SetSize(pElement->GetSize());
	TryCatch(r == E_SUCCESS, , "pPlaceholderPanel->SetSize");

	r = pPlaceholderPanel->AddControl(pElement);
	TryCatch(r == E_SUCCESS, , "pPlaceholderPanel->AddControl");


	itemLayout.SetSpacing(*pElement, 10);


//	r = AddControl(pPlaceholderPanel);
//	TryCatch(r == E_SUCCESS, , "Failed AddControl");

	mySize = GetSize();
	elementSize = pElement->GetSize();

//	if (mySize.width < elementSize.width) {
//		SetSize(elementSize.width, mySize.height + elementSize.height);
//	} else {
//		SetSize(mySize.width, mySize.height + elementSize.height);
//	}

	SetSize(pElement->GetSize().width+40, pElement->GetSize().height+20);

	AppLog("pElement size: %dx%d", pElement->GetWidth(), pElement->GetHeight());
	AppLog("pPlaceholderPanel size: %dx%d", pPlaceholderPanel->GetWidth(), pPlaceholderPanel->GetHeight());
	AppLog("Bubble size: %dx%d", GetWidth(), GetHeight());
	return r;

CATCH:
	AppLogException("MessageBubble::AddElement is failed. : %s", GetErrorMessage(r));
	return r;
}

result MessageBubble::OnDraw(void) {
	result r = E_SUCCESS;

	Canvas* pCanvas = GetCanvasN();
	Dimension screenSize = GetSize();
	Bitmap* pBubble;

	pBubble = (out == 1) ? pBubbleOut : pBubbleIn;

	// TODO: paddigns
	r = pCanvas->DrawNinePatchedBitmap(Rectangle(0, 0, screenSize.width, screenSize.height), *pBubble);
	TryCatch(r == E_SUCCESS, , "Failed DrawNinePatchedBitmap");

	delete pCanvas;
	return r;

CATCH:
	AppLogException("$${Function:OnDraw} is failed.", GetErrorMessage(r));
	delete pCanvas;
	return r;
}
