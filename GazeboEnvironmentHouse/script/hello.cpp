#include <gazebo/gazebo.hh>

namespace gazebo
{
    class WorldPluginMyRobot: public WorldPlugin
    {
        public: WorldPluginMyRobot() : WorldPlugin()
            {
                printf("This is my first Plugin to interact with the world\n\n");
            }
        public: void Load(physics::WorldPtr _world,sdf::ElementPtr _sdf)
            {

            }
    };
    GZ_REGISTER_WORLD_PLUGIN(WorldPluginMyRobot)  
}