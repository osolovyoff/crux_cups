#ifndef scene_h__
#define scene_h__

#include <vector>
#include "boost/shared_ptr.hpp"

enum {
	GAMEMENU  = 0,
	GAMESCENE = 1,
	TUTORIAL  = 2,
	DEVSCENE = 3,
	QUIT      = 4
};

class IScene
{
public:
	virtual void	Initialize() = 0;
	virtual int	    Update() = 0;
	virtual void	Render() = 0;
	virtual void	Release() = 0;
};

typedef boost::shared_ptr<IScene> ISceneShared;
typedef std::vector<ISceneShared> SceneVector;

#endif // scene_h__