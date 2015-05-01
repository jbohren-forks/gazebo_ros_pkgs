#include "gazebo/physics/physics.hh"
#include "gazebo/common/common.hh"
#include "gazebo/gazebo.hh"

namespace gazebo
{
  class GazeboInitialTime : public WorldPlugin
  {
  public:

    void Load(physics::WorldPtr _parent, sdf::ElementPtr _sdf)
    {
      world_ = _parent;

      bool initialize_with_wall_time = false;

      if (_sdf->HasElement("wall_time")) {
        initialize_with_wall_time = true;
        initial_time_ = gazebo::common::Time::GetWallTime();
      }

      if(not initialize_with_wall_time and _sdf->HasElement("specific_time")) {
        sdf::ElementPtr specific_time = _sdf->GetElement("specific_time");
        int32_t secs = 0;
        int32_t nsecs = 0;

        if(specific_time->HasElement("secs")) {
          secs = specific_time->GetElement("secs")->Get<int32_t>();
        }
        if(specific_time->HasElement("nsecs")) {
          nsecs = specific_time->GetElement("nsecs")->Get<int32_t>();
        }

        initial_time_.Set(secs, nsecs);
      }
    }

    virtual void Init()
    {
      world_->SetSimTime(initial_time_);
    }

  private:
    gazebo::physics::WorldPtr world_;
    gazebo::common::Time initial_time_;
  };

  // Register this plugin with the simulator
  GZ_REGISTER_WORLD_PLUGIN(GazeboInitialTime)
}

