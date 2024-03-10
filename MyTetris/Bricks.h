#include "Plates.h"

#include <time.h>
#include <stdlib.h>

class brick
{
public:
	int ycenter;
	int xcenter;
	int position;
	bool exist;
	Plate* fuild;
	virtual bool canrotate() { return true; };
	virtual bool canmoveright() { return true; };
	virtual bool canmoveleft() { return true; };
	virtual bool canmovedown() { return true; };
	virtual bool canbeputted() { return true; };
	virtual void movedown() { return; };
	virtual void moveleft() { return; };
	virtual void moveright() { return; };
	virtual void rotate() { return; };
	virtual void del() { return; };
	virtual void drow() { return; };
};
struct Tbrick : public brick
{
	Tbrick(Plate* f, int x, int y)
	{
		srand(time(NULL));
		ycenter = y;
		xcenter = x;
		position = rand()/4 + 100;
		fuild = f;
		exist = true;
		canbeputted();
	}
	bool canrotate() override
	{
		switch (position % 4)
		{
		case 0: if (fuild->f[ycenter - 1][xcenter].sq == "  ") { return true; }
			  else { return false; } break;
		case 1: if (fuild->f[ycenter][xcenter - 1].sq == "  ") { return true; }
			  else { return false; } break;
		case 2: if (fuild->f[ycenter + 1][xcenter].sq == "  ") { return true; }
			  else { return false; } break;
		case 3:if (fuild->f[ycenter][xcenter + 1].sq == "  ") { return true; }
			  else { return false; } break;
		}
	};
	bool canmoveright()  override
	{
		switch (position % 4)
		{
		case 0: if (fuild->f[ycenter][xcenter + 2].sq == "  " && fuild->f[ycenter + 1][xcenter + 1].sq == "  ") { return true; }
			  else { return false; } break;
		case 1: if (fuild->f[ycenter][xcenter + 2].sq == "  " && fuild->f[ycenter + 1][xcenter + 1].sq == "  " && fuild->f[ycenter - 1][xcenter + 1].sq == "  ") { return true; }
			  else { return false; } break;
		case 2: if (fuild->f[ycenter - 1][xcenter + 1].sq == "  " && fuild->f[ycenter][xcenter + 2].sq == "  ") { return true; }
			  else { return false; } break;
		case 3:if (fuild->f[ycenter][xcenter + 1].sq == "  " && fuild->f[ycenter + 1][xcenter + 1].sq == "  " && fuild->f[ycenter - 1][xcenter + 1].sq == "  ") { return true; }
			  else { return false; } break;
		}
	};
	bool canmoveleft()  override
	{
		switch (position % 4)
		{
		case 0: if (fuild->f[ycenter][xcenter - 2].sq == "  " && fuild->f[ycenter + 1][xcenter - 1].sq == "  ") { return true; }
			  else { return false; } break;
		case 1: if (fuild->f[ycenter][xcenter - 1].sq == "  " && fuild->f[ycenter + 1][xcenter - 1].sq == "  " && fuild->f[ycenter - 1][xcenter - 1].sq == "  ") { return true; }
			  else { return false; } break;
		case 2: if (fuild->f[ycenter - 1][xcenter - 1].sq == "  " && fuild->f[ycenter][xcenter - 2].sq == "  ") { return true; }
			  else { return false; } break;
		case 3:if (fuild->f[ycenter][xcenter - 2].sq == "  " && fuild->f[ycenter + 1][xcenter - 1].sq == "  " && fuild->f[ycenter - 1][xcenter - 1].sq == "  ") { return true; }
			  else { return false; } break;
		}
	};
	bool canmovedown() override
	{
		switch (position % 4)
		{
		case 0: if (fuild->f[ycenter + 2][xcenter].sq == "  " && fuild->f[ycenter + 1][xcenter + 1].sq == "  " && fuild->f[ycenter + 1][xcenter - 1].sq == "  ") { return true; }
			  else { return false; } break;
		case 1: if (fuild->f[ycenter + 1][xcenter + 1].sq == "  " && fuild->f[ycenter + 2][xcenter].sq == "  ") { return true; }
			  else { return false; } break;
		case 2: if (fuild->f[ycenter + 1][xcenter + 1].sq == "  " && fuild->f[ycenter + 1][xcenter - 1].sq == "  " && fuild->f[ycenter + 1][xcenter].sq == "  ") { return true; }
			  else { return false; } break;
		case 3:if (fuild->f[ycenter + 2][xcenter].sq == "  " && fuild->f[ycenter + 1][xcenter - 1].sq == "  ") { return true; }
			  else { return false; } break;
		}
	};
	bool canbeputted() override
	{
		if (fuild->f[3][7].sq == "  " && fuild->f[3][6].sq == "  " && fuild->f[3][8].sq == "  " && fuild->f[4][7].sq == "  ")
		{
			exist = true;
			return true;
		}
		else
		{
			exist = false;
			return false;
		}
	};
	void movedown() override
	{
		if (canmovedown())
		{
			del();
			ycenter++;
			drow();
		}
	};
	void moveleft() override
	{
		if (canmoveleft())
		{
			del();
			xcenter--;
			drow();
		}
	};
	void moveright() override
	{
		if (canmoveright())
		{
			del();
			xcenter++;
			drow();
		}
	};
	void rotate() override
	{
		if (canrotate())
		{
			del();
			position--;
			drow();
		}
	};
	void del() override
	{
		switch (position % 4)
		{
		case 0: fuild->f[ycenter][xcenter].sq = "  "; fuild->f[ycenter + 1][xcenter].sq = "  "; fuild->f[ycenter][xcenter - 1].sq = "  "; fuild->f[ycenter][xcenter + 1].sq = "  "; break;
		case 1: fuild->f[ycenter][xcenter].sq = "  "; fuild->f[ycenter + 1][xcenter].sq = "  "; fuild->f[ycenter - 1][xcenter].sq = "  "; fuild->f[ycenter][xcenter + 1].sq = "  "; break;
		case 2: fuild->f[ycenter][xcenter].sq = "  "; fuild->f[ycenter - 1][xcenter].sq = "  "; fuild->f[ycenter][xcenter - 1].sq = "  "; fuild->f[ycenter][xcenter + 1].sq = "  "; break;
		case 3: fuild->f[ycenter][xcenter].sq = "  "; fuild->f[ycenter + 1][xcenter].sq = "  "; fuild->f[ycenter][xcenter - 1].sq = "  "; fuild->f[ycenter - 1][xcenter].sq = "  "; break;
		}
	}
	void drow() override
	{
		switch (position % 4)
		{
		case 0: fuild->f[ycenter][xcenter].sq = "[]"; fuild->f[ycenter + 1][xcenter].sq = "[]"; fuild->f[ycenter][xcenter - 1].sq = "[]"; fuild->f[ycenter][xcenter + 1].sq = "[]"; break;
		case 1: fuild->f[ycenter][xcenter].sq = "[]"; fuild->f[ycenter + 1][xcenter].sq = "[]"; fuild->f[ycenter - 1][xcenter].sq = "[]"; fuild->f[ycenter][xcenter + 1].sq = "[]"; break;
		case 2: fuild->f[ycenter][xcenter].sq = "[]"; fuild->f[ycenter - 1][xcenter].sq = "[]"; fuild->f[ycenter][xcenter - 1].sq = "[]"; fuild->f[ycenter][xcenter + 1].sq = "[]"; break;
		case 3: fuild->f[ycenter][xcenter].sq = "[]"; fuild->f[ycenter + 1][xcenter].sq = "[]"; fuild->f[ycenter][xcenter - 1].sq = "[]"; fuild->f[ycenter - 1][xcenter].sq = "[]"; break;
		}
	};
};
struct Linebrick : public brick
{
	Linebrick(Plate* f, int x, int y)
	{
		ycenter = y;
		xcenter = x;
		position = rand() / 4 + 100;
		fuild = f;
		exist = true;
		if (canbeputted())
		{
			exist = true;
		}
	}
	bool canrotate() override
	{
		switch (position % 2)
		{
		case 0: if (fuild->f[ycenter - 1][xcenter].sq == "  " && fuild->f[ycenter + 1][xcenter].sq == "  " && fuild->f[ycenter + 2][xcenter].sq == "  ") { return true; }
			  else { return false; } break;
		case 1: if (fuild->f[ycenter][xcenter - 1].sq == "  " && fuild->f[ycenter][xcenter + 1].sq == "  " && fuild->f[ycenter][xcenter + 2].sq == "  ") { return true; }
			  else { return false; } break;
		}
	};
	bool canmoveright() override
	{
		switch (position % 2)
		{
		case 0: if (fuild->f[ycenter][xcenter + 3].sq == "  ") { return true; }
			  else { return false; } break;
		case 1: if (fuild->f[ycenter - 1][xcenter + 1].sq == "  " && fuild->f[ycenter][xcenter + 1].sq == "  " && fuild->f[ycenter + 1][xcenter + 1].sq == "  " && fuild->f[ycenter + 2][xcenter + 1].sq == "  ") { return true; }
			  else { return false; } break;
		}
	};
	bool canmoveleft() override
	{
		switch (position % 2)
		{
		case 0: if (fuild->f[ycenter][xcenter - 2].sq == "  ") { return true; }
			  else { return false; } break;
		case 1: if (fuild->f[ycenter - 1][xcenter - 1].sq == "  " && fuild->f[ycenter][xcenter - 1].sq == "  " && fuild->f[ycenter + 1][xcenter - 1].sq == "  " && fuild->f[ycenter + 2][xcenter - 1].sq == "  ") { return true; }
			  else { return false; } break;
		}
	};
	bool canmovedown() override
	{
		switch (position % 2)
		{
		case 0: if (fuild->f[ycenter + 1][xcenter].sq == "  " && fuild->f[ycenter + 1][xcenter - 1].sq == "  " && fuild->f[ycenter + 1][xcenter + 1].sq == "  " && fuild->f[ycenter + 1][xcenter + 2].sq == "  ") { return true; }
			  else { return false; } break;
		case 1: if (fuild->f[ycenter + 3][xcenter].sq == "  ") { return true; }
			  else { return false; } break;
		}
	};
	bool canbeputted() override
	{
		if (fuild->f[ycenter][xcenter - 1].sq == "  " && fuild->f[ycenter][xcenter].sq == "  " && fuild->f[ycenter][xcenter + 1].sq == "  " && fuild->f[ycenter][xcenter + 2].sq == "  ") { exist = true; return true; }
		else { fuild->gameover = true; exist = false; return false; }
	};
	void movedown() override
	{
		if (canmovedown())
		{
			del();
			ycenter++;
			drow();
		}
	};
	void moveleft() override
	{
		if (canmoveleft())
		{
			del();
			xcenter--;
			drow();
		}
	};
	void moveright() override
	{
		if (canmoveright())
		{
			del();
			xcenter++;
			drow();
		}
	};
	void rotate() override
	{
		if (canrotate())
		{
			del();
			position--;
			drow();
		}
	};
	void del() override
	{
		switch (position % 2)
		{
		case 0: fuild->f[ycenter][xcenter].sq = "  "; fuild->f[ycenter][xcenter - 1].sq = "  "; fuild->f[ycenter][xcenter + 1].sq = "  "; fuild->f[ycenter][xcenter + 2].sq = "  "; break;
		case 1: fuild->f[ycenter][xcenter].sq = "  "; fuild->f[ycenter - 1][xcenter].sq = "  "; fuild->f[ycenter + 1][xcenter].sq = "  "; fuild->f[ycenter + 2][xcenter].sq = "  "; break;
		}
	};
	void drow() override
	{
		switch (position % 2)
		{
		case 0: fuild->f[ycenter][xcenter].sq = "[]"; fuild->f[ycenter][xcenter - 1].sq = "[]"; fuild->f[ycenter][xcenter + 1].sq = "[]"; fuild->f[ycenter][xcenter + 2].sq = "[]"; break;
		case 1: fuild->f[ycenter][xcenter].sq = "[]"; fuild->f[ycenter - 1][xcenter].sq = "[]"; fuild->f[ycenter + 1][xcenter].sq = "[]"; fuild->f[ycenter + 2][xcenter].sq = "[]"; break;
		}
	};
};
struct Lbrick : public brick
{
	Lbrick(Plate* f, int x, int y)
	{
		ycenter = y;
		xcenter = x;
		position = rand() / 4 + 100;
		fuild = f;
		exist = true;
		if (canbeputted())
		{
			exist = true;
		}
	}
	bool canrotate() override
	{
		switch (position % 4)
		{
		case 0: if (fuild->f[ycenter + 1][xcenter - 1].sq == "  " && fuild->f[ycenter + 1][xcenter].sq == "  ") { return true; }
			  else { return false; } break;
		case 1: if (fuild->f[ycenter][xcenter + 1].sq == "  " && fuild->f[ycenter + 1][xcenter + 1].sq == "  ") { return true; }
			  else { return false; } break;
		case 2:if (fuild->f[ycenter - 1][xcenter].sq == "  " && fuild->f[ycenter - 1][xcenter + 1].sq == "  ") { return true; }
			  else { return false; } break;
		case 3: if (fuild->f[ycenter][xcenter - 1].sq == "  " && fuild->f[ycenter - 1][xcenter - 1].sq == "  ") { return true; }
			  else { return false; } break;
		}
	};
	bool canmoveright() override
	{
		switch (position % 4)
		{
		case 0: if (fuild->f[ycenter][xcenter].sq == "  " && fuild->f[ycenter - 1][xcenter + 2].sq == "  ") { return true; }
			  else { return false; } break;
		case 1: if (fuild->f[ycenter][xcenter].sq == "  " && fuild->f[ycenter - 1][xcenter].sq == "  " && fuild->f[ycenter + 1][xcenter + 1].sq == "  ") { return true; }
			  else { return false; } break;
		case 2:if (fuild->f[ycenter][xcenter + 2].sq == "  " && fuild->f[ycenter + 1][xcenter + 2].sq == "  ") { return true; }
			  else { return false; } break;
		case 3: if (fuild->f[ycenter][xcenter + 2].sq == "  " && fuild->f[ycenter + 1][xcenter + 2].sq == "  " && fuild->f[ycenter - 1][xcenter + 2].sq == "  ") { return true; }
			  else { return false; } break;
		}
	};
	bool canmoveleft() override
	{
		switch (position % 4)
		{
		case 0: if (fuild->f[ycenter][xcenter - 2].sq == "  " && fuild->f[ycenter - 1][xcenter - 2].sq == "  ") { return true; }
			  else { return false; } break;
		case 1: if (fuild->f[ycenter][xcenter - 2].sq == "  " && fuild->f[ycenter - 1][xcenter - 2].sq == "  " && fuild->f[ycenter + 1][xcenter - 2].sq == "  ") { return true; }
			  else { return false; } break;
		case 2:if (fuild->f[ycenter + 1][xcenter - 2].sq == "  " && fuild->f[ycenter][xcenter].sq == "  ") { return true; }
			  else { return false; } break;
		case 3: if (fuild->f[ycenter][xcenter].sq == "  " && fuild->f[ycenter + 1][xcenter].sq == "  " && fuild->f[ycenter - 1][xcenter - 1].sq == "  ") { return true; }
			  else { return false; } break;
		}
	};
	bool canmovedown() override
	{
		switch (position % 4)
		{
		case 0: if (fuild->f[ycenter][xcenter].sq == "  " && fuild->f[ycenter + 1][xcenter - 1].sq == "  " && fuild->f[ycenter][xcenter + 1].sq == "  ") { return true; }
			  else { return false; } break;
		case 1: if (fuild->f[ycenter + 2][xcenter].sq == "  " && fuild->f[ycenter + 2][xcenter - 1].sq == "  ") { return true; }
			  else { return false; } break;
		case 2:if (fuild->f[ycenter + 2][xcenter + 1].sq == "  " && fuild->f[ycenter + 2][xcenter - 1].sq == "  " && fuild->f[ycenter + 2][xcenter].sq == "  ") { return true; }
			  else { return false; } break;
		case 3: if (fuild->f[ycenter][xcenter].sq == "  " && fuild->f[ycenter + 2][xcenter + 1].sq == "  ") { return true; }
			  else { return false; } break;
		}
	};
	bool canbeputted() override
	{
		if (fuild->f[ycenter][xcenter].sq == "  " && fuild->f[ycenter + 1][xcenter].sq == "  " && fuild->f[ycenter][xcenter + 1].sq == "  " && fuild->f[ycenter][xcenter + 2].sq == "  ")
		{
			exist = true;
			return true;
		}
		else
		{
			fuild->gameover = true;
			exist = false;
			return true;
		}
	};
	void movedown() override
	{
		if (canmovedown())
		{
			del();
			ycenter++;
			drow();
		}
	};
	void moveleft() override
	{
		if (canmoveleft())
		{
			del();
			xcenter--;
			drow();
		}
	};
	void moveright() override
	{
		if (canmoveright())
		{
			del();
			xcenter++;
			drow();
		}
	};
	void rotate() override
	{
		if (canrotate())
		{
			del();
			position--;
			drow();
		}
	};
	void del() override
	{
		switch (position % 4)
		{
		case 0: fuild->f[ycenter][xcenter - 1].sq = "  "; fuild->f[ycenter - 1][xcenter - 1].sq = "  "; fuild->f[ycenter - 1][xcenter].sq = "  "; fuild->f[ycenter - 1][xcenter + 1].sq = "  "; break;
		case 1: fuild->f[ycenter][xcenter - 1].sq = "  "; fuild->f[ycenter + 1][xcenter - 1].sq = "  "; fuild->f[ycenter + 1][xcenter].sq = "  "; fuild->f[ycenter - 1][xcenter - 1].sq = "  "; break;
		case 2: fuild->f[ycenter][xcenter + 1].sq = "  "; fuild->f[ycenter + 1][xcenter + 1].sq = "  "; fuild->f[ycenter + 1][xcenter].sq = "  "; fuild->f[ycenter + 1][xcenter - 1].sq = "  "; break;
		case 3: fuild->f[ycenter - 1][xcenter].sq = "  "; fuild->f[ycenter - 1][xcenter + 1].sq = "  "; fuild->f[ycenter][xcenter + 1].sq = "  "; fuild->f[ycenter + 1][xcenter + 1].sq = "  "; break;
		}
	};
	void drow() override
	{
		switch (position % 4)
		{
		case 0: fuild->f[ycenter][xcenter - 1].sq = "[]"; fuild->f[ycenter - 1][xcenter - 1].sq = "[]"; fuild->f[ycenter - 1][xcenter].sq = "[]"; fuild->f[ycenter - 1][xcenter + 1].sq = "[]"; break;
		case 1: fuild->f[ycenter][xcenter - 1].sq = "[]"; fuild->f[ycenter + 1][xcenter - 1].sq = "[]"; fuild->f[ycenter + 1][xcenter].sq = "[]"; fuild->f[ycenter - 1][xcenter - 1].sq = "[]"; break;
		case 2: fuild->f[ycenter][xcenter + 1].sq = "[]"; fuild->f[ycenter + 1][xcenter + 1].sq = "[]"; fuild->f[ycenter + 1][xcenter].sq = "[]"; fuild->f[ycenter + 1][xcenter - 1].sq = "[]"; break;
		case 3: fuild->f[ycenter - 1][xcenter].sq = "[]"; fuild->f[ycenter - 1][xcenter + 1].sq = "[]"; fuild->f[ycenter][xcenter + 1].sq = "[]"; fuild->f[ycenter + 1][xcenter + 1].sq = "[]"; break;
		}
	};
};
struct RLbrick : public brick
{
	RLbrick(Plate* f, int x, int y)
	{
		ycenter = y;
		xcenter = x;
		position = rand() / 4 + 100;
		fuild = f;
		exist = true;
		if (canbeputted())
		{
			exist = true;
		}
	}
	bool canrotate() override
	{
		switch (position % 4)
		{
		case 0: if (fuild->f[ycenter][xcenter + 1].sq == "  " && fuild->f[ycenter - 1][xcenter + 1].sq == "  ") { return true; }
			  else { return false; } break;
		case 1: if (fuild->f[ycenter - 1][xcenter].sq == "  " && fuild->f[ycenter - 1][xcenter - 1].sq == "  ") { return true; }
			  else { return false; } break;
		case 2:if (fuild->f[ycenter][xcenter - 1].sq == "  " && fuild->f[ycenter + 1][xcenter - 1].sq == "  ") { return true; }
			  else { return false; } break;
		case 3: if (fuild->f[ycenter + 1][xcenter].sq == "  " && fuild->f[ycenter + 1][xcenter + 1].sq == "  ") { return true; }
			  else { return false; } break;
		}
	};
	bool canmoveright() override
	{
		switch (position % 4)
		{
		case 0: if (fuild->f[ycenter][xcenter].sq == "  " && fuild->f[ycenter + 1][xcenter + 2].sq == "  ") { return true; }
			  else { return false; } break;
		case 1: if (fuild->f[ycenter][xcenter + 2].sq == "  " && fuild->f[ycenter - 1][xcenter + 2].sq == "  " && fuild->f[ycenter + 1][xcenter + 2].sq == "  ") { return true; }
			  else { return false; } break;
		case 2:if (fuild->f[ycenter - 1][xcenter + 2].sq == "  " && fuild->f[ycenter][xcenter + 2].sq == "  ") { return true; }
			  else { return false; } break;
		case 3: if (fuild->f[ycenter][xcenter].sq == "  " && fuild->f[ycenter + 1][xcenter].sq == "  " && fuild->f[ycenter - 1][xcenter + 1].sq == "  ") { return true; }
			  else { return false; } break;
		}
	};
	bool canmoveleft() override
	{
		switch (position % 4)
		{
		case 0: if (fuild->f[ycenter + 1][xcenter - 2].sq == "  " && fuild->f[ycenter][xcenter - 2].sq == "  ") { return true; }
			  else { return false; } break;
		case 1: if (fuild->f[ycenter][xcenter].sq == "  " && fuild->f[ycenter - 1][xcenter].sq == "  " && fuild->f[ycenter + 1][xcenter - 1].sq == "  ") { return true; }
			  else { return false; } break;
		case 2:if (fuild->f[ycenter][xcenter].sq == "  " && fuild->f[ycenter - 1][xcenter - 2].sq == "  ") { return true; }
			  else { return false; } break;
		case 3: if (fuild->f[ycenter][xcenter - 2].sq == "  " && fuild->f[ycenter + 1][xcenter - 2].sq == "  " && fuild->f[ycenter - 1][xcenter - 2].sq == "  ") { return true; }
			  else { return false; } break;
		}
	};
	bool canmovedown() override
	{
		switch (position % 4)
		{
		case 0: if (fuild->f[ycenter + 2][xcenter - 1].sq == "  " && fuild->f[ycenter + 2][xcenter + 1].sq == "  " && fuild->f[ycenter + 2][xcenter].sq == "  ") { return true; }
			  else { return false; } break;
		case 1: if (fuild->f[ycenter + 2][xcenter].sq == "  " && fuild->f[ycenter + 2][xcenter + 1].sq == "  ") { return true; }
			  else { return false; } break;
		case 2:if (fuild->f[ycenter][xcenter].sq == "  " && fuild->f[ycenter + 1][xcenter + 1].sq == "  " && fuild->f[ycenter][xcenter - 1].sq == "  ") { return true; }
			  else { return false; } break;
		case 3: if (fuild->f[ycenter][xcenter].sq == "  " && fuild->f[ycenter + 2][xcenter - 1].sq == "  ") { return true; }
			  else { return false; } break;
		}
	};
	bool canbeputted() override
	{
		if (fuild->f[ycenter][xcenter - 1].sq == "  " && fuild->f[ycenter + 1][xcenter - 1].sq == "  " && fuild->f[ycenter + 1][xcenter].sq == "  " && fuild->f[ycenter + 1][xcenter + 1].sq == "  ") { exist = true; return true; }
		else { fuild->gameover = true; exist = false; return false; }
	};
	void movedown() override
	{
		if (canmovedown())
		{
			del();
			ycenter++;
			drow();
		}
	};
	void moveleft() override
	{
		if (canmoveleft())
		{
			del();
			xcenter--;
			drow();
		}
	};
	void moveright() override
	{
		if (canmoveright())
		{
			del();
			xcenter++;
			drow();
		}
	};
	void rotate() override
	{
		if (canrotate())
		{
			del();
			position++;
			drow();
		}
	};
	void del() override
	{
		switch (position % 4)
		{
		case 0: fuild->f[ycenter][xcenter - 1].sq = "  "; fuild->f[ycenter + 1][xcenter - 1].sq = "  "; fuild->f[ycenter + 1][xcenter + 1].sq = "  "; fuild->f[ycenter + 1][xcenter].sq = "  "; break;
		case 1: fuild->f[ycenter + 1][xcenter].sq = "  "; fuild->f[ycenter + 1][xcenter + 1].sq = "  "; fuild->f[ycenter][xcenter + 1].sq = "  "; fuild->f[ycenter + 1][xcenter + 1].sq = "  "; break;
		case 2: fuild->f[ycenter][xcenter + 1].sq = "  "; fuild->f[ycenter - 1][xcenter + 1].sq = "  "; fuild->f[ycenter - 1][xcenter].sq = "  "; fuild->f[ycenter - 1][xcenter - 1].sq = "  "; break;
		case 3: fuild->f[ycenter - 1][xcenter].sq = "  "; fuild->f[ycenter - 1][xcenter - 1].sq = "  "; fuild->f[ycenter][xcenter - 1].sq = "  "; fuild->f[ycenter + 1][xcenter - 1].sq = "  "; break;
		}
	};
	void drow() override
	{
		switch (position % 4)
		{
		case 0: fuild->f[ycenter][xcenter - 1].sq = "[]"; fuild->f[ycenter + 1][xcenter - 1].sq = "[]"; fuild->f[ycenter + 1][xcenter + 1].sq = "[]"; fuild->f[ycenter + 1][xcenter].sq = "[]"; break;
		case 1: fuild->f[ycenter + 1][xcenter].sq = "[]"; fuild->f[ycenter + 1][xcenter + 1].sq = "[]"; fuild->f[ycenter][xcenter + 1].sq = "[]"; fuild->f[ycenter + 1][xcenter + 1].sq = "[]"; break;
		case 2: fuild->f[ycenter][xcenter + 1].sq = "[]"; fuild->f[ycenter - 1][xcenter + 1].sq = "[]"; fuild->f[ycenter - 1][xcenter].sq = "[]"; fuild->f[ycenter - 1][xcenter - 1].sq = "[]"; break;
		case 3: fuild->f[ycenter - 1][xcenter].sq = "[]"; fuild->f[ycenter - 1][xcenter - 1].sq = "[]"; fuild->f[ycenter][xcenter - 1].sq = "[]"; fuild->f[ycenter + 1][xcenter - 1].sq = "[]"; break;
		}
	};
};
struct Zbrick : public brick
{
	Zbrick(Plate* f, int x, int y)
	{
		ycenter = y;
		xcenter = x;
		position = rand() / 4 + 100;
		fuild = f;
		exist = true;
		if (canbeputted())
		{
			exist = true;
		}
	}
	bool canrotate() override
	{
		switch (position % 2)
		{
		case 0: if (fuild->f[ycenter - 1][xcenter].sq == "  " && fuild->f[ycenter - 1][xcenter - 1].sq == "  ") { return true; }
			  else { return false; } break;
		case 1: if (fuild->f[ycenter + 1][xcenter].sq == "  " && fuild->f[ycenter + 1][xcenter + 1].sq == "  ") { return true; }
			  else { return false; } break;
		}
	};
	bool canmoveright() override
	{
		switch (position % 2)
		{
		case 0: if (fuild->f[ycenter][xcenter + 1].sq == "  " && fuild->f[ycenter + 1][xcenter + 2].sq == "  ") { return true; }
			  else { return false; } break;
		case 1: if (fuild->f[ycenter][xcenter + 1].sq == "  " && fuild->f[ycenter + 1][xcenter].sq == "  " && fuild->f[ycenter - 1][xcenter + 1].sq == "  ") { return true; }
			  else { return false; } break;
		}
	};
	bool canmoveleft() override
	{
		switch (position % 2)
		{
		case 0: if (fuild->f[ycenter][xcenter - 2].sq == "  " && fuild->f[ycenter + 1][xcenter - 1].sq == "  ") { return true; }
			  else { return false; } break;
		case 1: if (fuild->f[ycenter][xcenter - 2].sq == "  " && fuild->f[ycenter - 1][xcenter - 1].sq == "  " && fuild->f[ycenter + 1][xcenter - 2].sq == "  ") { return true; }
			  else { return false; } break;
		}
	};
	bool canmovedown() override
	{
		switch (position % 2)
		{
		case 0: if (fuild->f[ycenter + 1][xcenter - 1].sq == "  " && fuild->f[ycenter + 2][xcenter].sq == "  " && fuild->f[ycenter + 2][xcenter + 1].sq == "  ") { return true; }
			  else { return false; } break;
		case 1: if (fuild->f[ycenter + 1][xcenter].sq == "  " && fuild->f[ycenter + 2][xcenter - 1].sq == "  ") { return true; }
			  else { return false; } break;
		}
	};
	bool canbeputted() override
	{
		if (fuild->f[ycenter][xcenter].sq == "  " && fuild->f[ycenter][xcenter - 1].sq == "  " && fuild->f[ycenter + 1][xcenter].sq == "  " && fuild->f[ycenter + 1][xcenter + 1].sq == "  ")
		{
			exist = true;
			return true;
		}
		else
		{
			fuild->gameover = true;
			exist = false;
			return false;
		}
	};
	void movedown() override
	{
		if (canmovedown())
		{
			del();
			ycenter++;
			drow();
		}
	};
	void moveleft() override
	{
		if (canmoveleft())
		{
			del();
			xcenter--;
			drow();
		}
	};
	void moveright() override
	{
		if (canmoveright())
		{
			del();
			xcenter++;
			drow();
		}
	};
	void rotate() override
	{
		if (canrotate())
		{
			del();
			position++;
			drow();
		}
	};
	void del() override
	{
		switch (position % 2)
		{
		case 0: fuild->f[ycenter][xcenter].sq = "  "; fuild->f[ycenter][xcenter - 1].sq = "  "; fuild->f[ycenter + 1][xcenter].sq = "  "; fuild->f[ycenter + 1][xcenter + 1].sq = "  "; break;
		case 1: fuild->f[ycenter][xcenter].sq = "  "; fuild->f[ycenter - 1][xcenter].sq = "  "; fuild->f[ycenter][xcenter - 1].sq = "  "; fuild->f[ycenter + 1][xcenter - 1].sq = "  "; break;
		}
	};
	void drow() override
	{
		switch (position % 2)
		{
		case 0: fuild->f[ycenter][xcenter].sq = "[]"; fuild->f[ycenter][xcenter - 1].sq = "[]"; fuild->f[ycenter + 1][xcenter].sq = "[]"; fuild->f[ycenter + 1][xcenter + 1].sq = "[]"; break;
		case 1: fuild->f[ycenter][xcenter].sq = "[]"; fuild->f[ycenter - 1][xcenter].sq = "[]"; fuild->f[ycenter][xcenter - 1].sq = "[]"; fuild->f[ycenter + 1][xcenter - 1].sq = "[]"; break;
		}
	};
};
struct RZbrick : public brick
{
	RZbrick(Plate* f, int x, int y)
	{
		ycenter = y;
		xcenter = x;
		position = rand() / 4 + 100;
		fuild = f;
		exist = true;
		if (canbeputted())
		{
			exist = true;
		}
	}
	bool canrotate() override
	{
		switch (position % 2)
		{
		case 0: if (fuild->f[ycenter - 1][xcenter].sq == "  " && fuild->f[ycenter + 1][xcenter + 1].sq == "  ") { return true; }
			  else { return false; } break;
		case 1: if (fuild->f[ycenter + 1][xcenter].sq == "  " && fuild->f[ycenter + 1][xcenter - 1].sq == "  ") { return true; }
			  else { return false; } break;
		}
	};
	bool canmoveright() override
	{
		switch (position % 2)
		{
		case 0: if (fuild->f[ycenter + 1][xcenter + 1].sq == "  " && fuild->f[ycenter][xcenter + 2].sq == "  ") { return true; }
			  else { return false; } break;
		case 1: if (fuild->f[ycenter - 1][xcenter + 1].sq == "  " && fuild->f[ycenter][xcenter + 2].sq == "  " && fuild->f[ycenter + 1][xcenter + 2].sq == "  ") { return true; }
			  else { return false; } break;
		}
	};
	bool canmoveleft() override
	{
		switch (position % 2)
		{
		case 0: if (fuild->f[ycenter + 1][xcenter - 2].sq == "  " && fuild->f[ycenter][xcenter - 1].sq == "  ") { return true; }
			  else { return false; } break;
		case 1: if (fuild->f[ycenter][xcenter - 1].sq == "  " && fuild->f[ycenter - 1][xcenter - 1].sq == "  " && fuild->f[ycenter + 1][xcenter].sq == "  ") { return true; }
			  else { return false; } break;
		}
	};
	bool canmovedown() override
	{
		switch (position % 2)
		{
		case 0: if (fuild->f[ycenter + 2][xcenter].sq == "  " && fuild->f[ycenter + 2][xcenter - 1].sq == "  " && fuild->f[ycenter + 1][xcenter + 1].sq == "  ") { return true; }
			  else { return false; } break;
		case 1: if (fuild->f[ycenter + 2][xcenter + 1].sq == "  " && fuild->f[ycenter + 1][xcenter].sq == "  ") { return true; }
			  else { return false; } break;
		}
	};
	bool canbeputted() override
	{
		if (fuild->f[ycenter][xcenter].sq == "  " && fuild->f[ycenter][xcenter + 1].sq == "  " && fuild->f[ycenter + 1][xcenter].sq == "  " && fuild->f[ycenter + 1][xcenter - 1].sq == "  ")
		{
			exist = true;
			return true;
		}
		else
		{
			fuild->gameover = true;
			exist = false;
			return false;
		}
	};
	void movedown() override
	{
		if (canmovedown())
		{
			del();
			ycenter++;
			drow();
		}
	};
	void moveleft() override
	{
		if (canmoveleft())
		{
			del();
			xcenter--;
			drow();
		}
	};
	void moveright() override
	{
		if (canmoveright())
		{
			del();
			xcenter++;
			drow();
		}
	};
	void rotate() override
	{
		if (canrotate())
		{
			del();
			position++;
			drow();
		}
	};
	void del() override
	{
		switch (position % 2)
		{
		case 0: fuild->f[ycenter][xcenter].sq = "  "; fuild->f[ycenter][xcenter + 1].sq = "  "; fuild->f[ycenter + 1][xcenter].sq = "  "; fuild->f[ycenter + 1][xcenter - 1].sq = "  "; break;
		case 1: fuild->f[ycenter][xcenter].sq = "  "; fuild->f[ycenter - 1][xcenter].sq = "  "; fuild->f[ycenter][xcenter + 1].sq = "  "; fuild->f[ycenter + 1][xcenter + 1].sq = "  "; break;
		}
	};
	void drow() override
	{
		switch (position % 2)
		{
		case 0: fuild->f[ycenter][xcenter].sq = "[]"; fuild->f[ycenter][xcenter + 1].sq = "[]"; fuild->f[ycenter + 1][xcenter].sq = "[]"; fuild->f[ycenter + 1][xcenter - 1].sq = "[]"; break;
		case 1: fuild->f[ycenter][xcenter].sq = "[]"; fuild->f[ycenter - 1][xcenter].sq = "[]"; fuild->f[ycenter][xcenter + 1].sq = "[]"; fuild->f[ycenter + 1][xcenter + 1].sq = "[]"; break;
		}
	};
};
struct SQbrick : public brick
{
	SQbrick(Plate* f, int x, int y)
	{
		ycenter = y;
		xcenter = x;
		position = rand() / 4 + 100;
		fuild = f;
		exist = true;
		if (canbeputted())
		{
			exist = true;
		}
	}
	bool canrotate() override
	{
		return true;
	};
	bool canmoveright() override
	{
		if (fuild->f[ycenter][xcenter + 2].sq == "  " && fuild->f[ycenter + 1][xcenter + 2].sq == "  ") { return true; }
		else { return false; }
	};
	bool canmoveleft() override
	{
		if (fuild->f[ycenter][xcenter - 1].sq == "  " && fuild->f[ycenter + 1][xcenter - 1].sq == "  ") { return true; }
		else { return false; }
	};
	bool canmovedown() override
	{
		if (fuild->f[ycenter + 2][xcenter].sq == "  " && fuild->f[ycenter + 2][xcenter + 1].sq == "  ") { return true; }
		else { return false; }
	};
	bool canbeputted() override
	{
		if (fuild->f[ycenter][xcenter].sq == "  " && fuild->f[ycenter][xcenter + 1].sq == "  " && fuild->f[ycenter + 1][xcenter].sq == "  " && fuild->f[ycenter + 1][xcenter + 1].sq == "  ")
		{
			exist = true;
			return true;
		}
		else
		{
			fuild->gameover = true;
			exist = false;
			return false;
		}
	};
	void movedown() override
	{
		if (canmovedown())
		{
			del();
			ycenter++;
			drow();
		}
	};
	void moveleft() override
	{
		if (canmoveleft())
		{
			del();
			xcenter--;
			drow();
		}
	};
	void moveright() override
	{
		if (canmoveright())
		{
			del();
			xcenter++;
			drow();
		}
	};
	void rotate() override
	{
		if (canrotate())
		{
			del();
			position++;
			drow();
		}
	};
	void del() override
	{
		fuild->f[ycenter][xcenter].sq = "  "; fuild->f[ycenter][xcenter + 1].sq = "  "; fuild->f[ycenter + 1][xcenter].sq = "  "; fuild->f[ycenter + 1][xcenter + 1].sq = "  ";
	};
	void drow() override
	{
		fuild->f[ycenter][xcenter].sq = "[]"; fuild->f[ycenter][xcenter + 1].sq = "[]"; fuild->f[ycenter + 1][xcenter].sq = "[]"; fuild->f[ycenter + 1][xcenter + 1].sq = "[]";
	};
};