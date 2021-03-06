#ifndef __servicehdmi_h
#define __servicehdmi_h

#include <lib/base/message.h>
#include <lib/service/iservice.h>

class eStaticServiceHDMIInfo;

class eServiceFactoryHDMI: public iServiceHandler
{
	DECLARE_REF(eServiceFactoryHDMI);
public:
	eServiceFactoryHDMI();
	virtual ~eServiceFactoryHDMI();
	enum { id = 0x2000 };

	RESULT play(const eServiceReference &, ePtr<iPlayableService> &ptr);
	RESULT record(const eServiceReference &, ePtr<iRecordableService> &ptr);
	RESULT list(const eServiceReference &, ePtr<iListableService> &ptr);
	RESULT info(const eServiceReference &, ePtr<iStaticServiceInformation> &ptr);
	RESULT offlineOperations(const eServiceReference &, ePtr<iServiceOfflineOperations> &ptr);
private:
	ePtr<eStaticServiceHDMIInfo> m_service_info;
};

class eStaticServiceHDMIInfo: public iStaticServiceInformation
{
	DECLARE_REF(eStaticServiceHDMIInfo);
	friend class eServiceFactoryHDMI;
	eStaticServiceHDMIInfo();
public:
	RESULT getName(const eServiceReference &ref, std::string &name);
	int getLength(const eServiceReference &ref);
	int getInfo(const eServiceReference &ref, int w);
	int isPlayable(const eServiceReference &ref, const eServiceReference &ignore, bool simulate) { return 1; }
	long long getFileSize(const eServiceReference &ref);
};

class eServiceHDMI: public iPlayableService, public iServiceInformation, public Object
{
	DECLARE_REF(eServiceHDMI);
public:
	virtual ~eServiceHDMI();

	RESULT connectEvent(const Slot2<void, iPlayableService*, int> &event, ePtr<eConnection> &connection);
	RESULT start();
	RESULT stop();
	RESULT setTarget(int target);

	RESULT pause(ePtr<iPauseableService> &ptr) { ptr = 0; return -1; }
	RESULT seek(ePtr<iSeekableService> &ptr) { ptr = 0; return -1; }
	RESULT audioTracks(ePtr<iAudioTrackSelection> &ptr) { ptr = 0; return -1; }
	RESULT audioChannel(ePtr<iAudioChannelSelection> &ptr) { ptr = 0; return -1; }
	RESULT subtitle(ePtr<iSubtitleOutput> &ptr) { ptr = 0; return -1; }
	RESULT audioDelay(ePtr<iAudioDelay> &ptr) { ptr = 0; return -1; }

	RESULT frontendInfo(ePtr<iFrontendInformation> &ptr) { ptr = 0; return -1; }
	RESULT subServices(ePtr<iSubserviceList> &ptr) { ptr = 0; return -1; }
	RESULT timeshift(ePtr<iTimeshiftService> &ptr) { ptr = 0; return -1; }
	RESULT cueSheet(ePtr<iCueSheet> &ptr) { ptr = 0; return -1; }

	RESULT rdsDecoder(ePtr<iRdsDecoder> &ptr) { ptr = 0; return -1; }
	RESULT keys(ePtr<iServiceKeys> &ptr) { ptr = 0; return -1; }
	RESULT stream(ePtr<iStreamableService> &ptr) { ptr = 0; return -1; }
	RESULT streamed(ePtr<iStreamedService> &ptr) { ptr = 0; return -1; }

	RESULT info(ePtr<iServiceInformation>&);

	RESULT getName(std::string &name);
	int getInfo(int w);
	std::string getInfoString(int w);
	ePtr<iServiceInfoContainer> getInfoObject(int w);

private:
	friend class eServiceFactoryHDMI;
	eServiceHDMI(eServiceReference ref);
	Signal2<void,iPlayableService*, int> m_event;
	eServiceReference m_ref;
	int m_decoder_index;
	ePtr<iTSMPEGDecoder> m_decoder;
};

#endif
