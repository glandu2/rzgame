#ifndef JOBRESOURCE_H
#define JOBRESOURCE_H

#include "RefDataLoader.h"
#include "Database/DbQueryJobCallback.h"
#include <unordered_map>
#include <stdint.h>

namespace GameServer {

struct JobResource {
	int32_t id;
	int32_t stat_id;
	int32_t job_class;
	int16_t job_depth;
	int16_t up_lv;
	int16_t up_jlv;
	int16_t available_job[4];
	//int32_t text_id;
	//int32_t icon_id;
	//std::string icon_file_name;
};

class JobResourceBinding : public RefDataLoaderHelper<JobResource, JobResourceBinding> {
	DECLARE_CLASS(GameServer::JobResourceBinding)
};

}

#endif // JOBRESOURCE_H