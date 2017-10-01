#ifndef GAMESERVER_CLIENTSESSION_H
#define GAMESERVER_CLIENTSESSION_H

#include "ConnectionHandler.h"
#include "GameTypes.h"
#include "NetSession/EncryptedSession.h"
#include "NetSession/PacketSession.h"
#include <memory>
#include <unordered_map>

#include "GameClient/TS_CS_ACCOUNT_WITH_AUTH.h"
#include "GameClient/TS_CS_CHARACTER_LIST.h"
#include "GameClient/TS_SC_RESULT.h"
#include "PacketEnums.h"

namespace GameServer {

class CharacterLight;
class Character;

class ClientSession : public EncryptedSession<PacketSession> {
	DECLARE_CLASS(GameServer::ClientSession)
public:
	static void init();
	static void deinit();

	ClientSession();

	uint32_t getAccountId() { return accountId; }
	std::string getAccount() { return account; }
	int getVersion() { return version; }

	void onAccountLoginResult(uint16_t result,
	                          std::string account,
	                          uint32_t accountId,
	                          char nPCBangUser,
	                          uint32_t nEventCode,
	                          uint32_t nAge,
	                          uint32_t nContinuousPlayTime,
	                          uint32_t nContinuousLogoutTime);
	void lobbyExitResult(TS_ResultCode result, std::unique_ptr<CharacterLight> characterData);
	void playerLoadingResult(TS_ResultCode result, std::unique_ptr<Character> character);

	template<typename T> typename std::enable_if<!std::is_pointer<T>::value, void>::type sendPacket(const T& packet) {
		PacketSession::sendPacket(packet, version);
	}

	void sendPacket(const TS_MESSAGE* packet) { PacketSession::sendPacket(packet); }
	void sendResult(uint16_t id, uint16_t result, int32_t value);
	void sendResult(const TS_MESSAGE* originalPacket, uint16_t result, int32_t value);
	void sendProperty(game_handle_t handle, const char* name, int64_t value);
	void sendProperty(game_handle_t handle, const char* name, const std::string& value);

protected:
	~ClientSession();

	EventChain<PacketSession> onPacketReceived(const TS_MESSAGE* packet);

	void onAccountWithAuth(const TS_CS_ACCOUNT_WITH_AUTH* packet);

	void setConnectionHandler(ConnectionHandler* newConnectionHandler);

private:
	int version;
	bool authReceived;
	std::string account;
	uint32_t accountId;
	std::unique_ptr<ConnectionHandler> connectionHandler;
	std::unique_ptr<ConnectionHandler> oldConnectionHandler;
};

}  // namespace GameServer

#endif  // GAMESERVER_CLIENTSESSION_H
