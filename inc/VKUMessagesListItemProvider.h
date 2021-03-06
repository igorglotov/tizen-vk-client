	/*
 * VKUMessagesListItemProvider.h
 *
 *  Created on: Nov 5, 2013
 *      Author: igorglotov
 */

#ifndef VKUMESSAGESLISTITEMPROVIDER_H_
#define VKUMESSAGESLISTITEMPROVIDER_H_

#include <FUi.h>
#include <FWebJson.h>
#include <FUiCtrlIListViewItemProvider.h>
#include <FBase.h>

class VKUMessagesListItemProvider;

#include "VKU.h"
#include "VKUApi.h"
#include "IAPIRequestListener.h"
#include "IReadEventListener.h"
#include "AppResourceId.h"
#include "MessageBubble.h"
#include "Requests.h"


class VKUMessagesListItemProvider :
	public Tizen::Ui::Controls::ITableViewItemProvider,
	public Tizen::Ui::Controls::ITableViewItemEventListener,
	public Tizen::Ui::Controls::IScrollEventListener,
	public IAPIRequestListener,
	public IReadEventListener {
public:
	VKUMessagesListItemProvider();
	virtual ~VKUMessagesListItemProvider();

	result Construct(int peerId, Tizen::Web::Json::JsonObject *chatJson, Tizen::Ui::Controls::TableView *tableView);
	// ITableViewItemProvider
	virtual int GetItemCount(void);
	virtual Tizen::Ui::Controls::TableViewItem* CreateItem(int itemIndex, int itemWidth);
	virtual bool DeleteItem(int itemIndex, Tizen::Ui::Controls::TableViewItem* pItem);
	virtual void UpdateItem(int itemIndex, Tizen::Ui::Controls::TableViewItem* pItem);
	virtual int GetDefaultItemHeight(void);

	// ITableViewItemEventListener
	virtual void OnTableViewItemStateChanged(
			Tizen::Ui::Controls::TableView& tableView, int itemIndex,
			Tizen::Ui::Controls::TableViewItem* pItem,
			Tizen::Ui::Controls::TableViewItemStatus status);

	virtual void OnTableViewContextItemActivationStateChanged(
			Tizen::Ui::Controls::TableView& tableView, int itemIndex,
			Tizen::Ui::Controls::TableViewContextItem* pContextItem,
			bool activated) {};

	virtual void OnTableViewItemReordered(
			Tizen::Ui::Controls::TableView& tableView, int itemIndexFrom,
			int itemIndexTo) {};

	// custom
	Tizen::Base::Collection::ArrayList * GetMessageElementsN(const Tizen::Web::Json::JsonObject *pMessageJson, int itemWidth);
	void RequestUpdateHistory();
	void RequestNewMessage(int messageId);
	void RequestLoadMore(int count);

	// IAPIRequestListener
	virtual void OnResponseN(RequestId requestId, Tizen::Web::Json::JsonObject *object);

	// IScrollEventListener
	virtual void OnScrollEndReached(Tizen::Ui::Control& source, Tizen::Ui::Controls::ScrollEndEvent type);

	// IReadEventListener
	virtual void OnReadEvent(int messageId);
private:
	Tizen::Web::Json::JsonObject* _chatJson; // NOTE: may be null
	Tizen::Web::Json::JsonArray* _messagesJson;
	Tizen::Ui::Controls::TableView * _tableView;

	Tizen::Base::Collection::HashMap * _pUserIdAvatarMap;

	int _peerId;

	result ProcessChatUsers(const Tizen::Web::Json::JsonObject * chatJson);

};

#endif /* VKUMESSAGESLISTITEMPROVIDER_H_ */
