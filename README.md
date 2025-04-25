# cvp
gitee：gitee.com/infdust/cvp\
qq群： 530737441
# 介绍————to 用户
cvp vs. (plants vs. zombies)\
pvz的mod加载器\
涉及文件：<font color="#50b0f0">启动器.exe 加载器.dll 插件.cvp</font>
## 用法
1. 游戏本体（PlantsVsZombies.exe）应使用<strong><font color="#ff4040">1.0.0.1051英文原版</strong></font>，其他版本无法兼容并且不会被识别
2. 启动器（.exe）应置于 <strong><font color="#ff4040">英文原版</strong></font>pvz同一目录下，启动后会在同目录下搜索加载器并运行加载器
3. 加载器（.dll）应置于 <strong><font color="#ff4040">英文原版</strong></font>pvz同一目录下，运行时会将当前目录下所有插件全部装载并启动pvz
4. 插件（.cvp）应置于 <strong><font color="#ff4040">英文原版</strong></font>pvz同一目录下，可根据需要任意安装，原则上各插件之间不会产生冲突，但在不同插件同时进行相互矛盾的行为时可能产生难以预料的结果
5. 将各文件添加进正确目录后，运行启动器即可
# 介绍————to 插件开发者
cvp vs. (plants vs. zombies)\
pvz的一套API，对外暴露其类、成员、方法及运行逻辑\
使用cvp编写插件模块，被主模块加载的插件模块可用于实现各种功能\
涉及文件：<font color="#50b0f0">template.h main.cpp</font>
## 接口
### <font color="#90c000">Functor接口</font>
- #### <font color="#30a0a0">Cvp::Functor<retT(argT...)></font>
	函数类，允许模块使用算子对函数进行操作以改变程序运行逻辑
	- 使用算子作用于Functor以改变其执行逻辑：
		```
		Functor& operator+=(std::function<retT(argT...)>);
		```
	- 在算子中用以指代原Functor本身：
		```
		static retT Recur(argT...);
		```
	- 例：
		```
		Functor<void(Plant*)> Attack;//植物攻击函数
		Attack += [](Plant* p)->void{//施加算子
			if(p->type == PEASHOOTER){//如果植物种类为豌豆射手
				return Attack.Recur(p);//调用原函数本身
			} else if(p->type == SNOWPEA){//寒冰射手
				Attack.Recur(p);
				Attack.Recur(p);//攻击两次
				return;
			} else {
				return;//不攻击
			} 
		};
		```
- #### <font color="#30a0a0">Functor<void(void)>& Cvp::DrawHook()</font>
	绘制函数，可使用算子
- #### <font color="#30a0a0">Functor<void(Cvp::KeyCode)>& Cvp::KeyHook()</font>
	按键函数，可使用算子
- #### <font color="#30a0a0">Functor<void(void)>& Cvp::UpdateHook()</font>
	刷新函数，可使用算子
- #### <font color="#30a0a0">Functor<void(void)>& Cvp::MainLoopHook()</font>
	程序进入主循环时调用一次，可使用算子
- #### <font color="#30a0a0">Functor<LRESULT \_\_stdcall(HWND, UINT, WPARAM, LPARAM)>& Cvp::WindProcook()</font>
	消息函数，可使用算子
### <font color="#90c000">Geo接口</font>
- #### <font color="#30a0a0">色彩</font>
	使用ARGB格式
	- 生成色彩：
		```
		DWORD UI::Geo::ARGB(DWORD r, DWORD g, DWORD b, DWORD a);
		```
	- 混合色彩，rate为color1的权重，取\[0, 1\]：
		```
		DWORD UI::Geo::Mix(DWORD color1, DWORD color2, float rate);
		```
	- 削弱/加强亮度/不透明度/饱和度，rate为作用强度，取\[0, 1\]：
		```
		DWORD UI::Geo::Dark(DWORD color, float rate);
		DWORD UI::Geo::Light(DWORD color, float rate);
		DWORD UI::Geo::Transp(DWORD color, float rate);
		DWORD UI::Geo::Opaque(DWORD color, float rate);
		DWORD UI::Geo::Dirty(DWORD color, float rate);
		DWORD UI::Geo::Pure(DWORD color, float rate);
		```
- #### <font color="#30a0a0">Ui::Geo</font>
	几何图形渲染类
	- 根据给出的坐标序列绘制折线：
		```
		static void Geo::DrawLine(DWORD color, Point<float>[] point, int pointNum);
		static void Geo::DrawLine(DWORD color, std::initializer_list<Point<float>> point);
		```
	- 根据给出的参数绘制空心/实心三角形：
		```
		static void Geo::DrawTriangle(DWORD color, Point<float> mid, float height, float width, float rotate);
		static void Geo::DrawFullTriangle(DWORD color, Point<float> mid, float height, float width, float rotate);
		static void Geo::DrawTriangle(DWORD color, Point<float> point1, Point<float> point2, Point<float> point3);
		static void Geo::DrawFullTriangle(DWORD color, Point<float> point1, Point<float> point2, Point<float> point3);
		```
	- 根据给出的参数绘制空心/实心圆角矩形：
		```
		static void Geo::DrawRect(DWORD color, Rect rect, float roundR);
		static void Geo::DrawFullRect(DWORD color, Rect rect, float roundR);
		```
	- 根据给出的参数绘制空心/实心圆：
		```
		static void Geo::DrawCircle(DWORD color, Point<float> mid, float radius);
		static void Geo::DrawFullCircle(DWORD color, Point<float> mid, float radius);
		```
	- 根据给出的参数绘制空心/实心正多边形：
		```
		static void Geo::DrawPolygon(DWORD color, int edgeNum, Point<float> mid, float radius, float rotate);
		static void Geo::DrawFullPolygon(DWORD color, int edgeNum, Point<float> mid, float radius, float rotate);
		```
	- 根据给出的参数绘制空心/实心任意多边形：
		```
		static void Geo::DrawPolygon(DWORD color, Point<float>[] point, int edgeNum);
		static void Geo::DrawFullPolygon(DWORD color, Point<float>[] point, int edgeNum);
		static void Geo::DrawPolygon(DWORD color, std::initializer_list<Point<float>> point);
		static void Geo::DrawFullPolygon(DWORD color, std::initializer_list<Point<float>> point);
		```
- #### <font color="#30a0a0">Ui::Geo::Vertex</font>
	几何顶点类
	- 构造顶点：
		```
		Ui::Geo::Vertex(int x, int y, DWORD color);
		Ui::Geo::Vertex(float x, float y, DWORD color);
		```
	- 根据给出的顶点序列进行绘制：
		```
		static void Ui::Geo::funcName(Ui::Geo::Vertex[] vertex, int num);
		static void Ui::Geo::funcName(std::vector<Ui::Geo::Vertex> vertex);
		static void Ui::Geo::funcName(std::array<Ui::Geo::Vertex, len> vertex);
		static void Ui::Geo::funcName(std::initializer_list<Ui::Geo::Vertex> vertex);
		```
	- 根据给出的色彩及坐标序列进行绘制：
		```
		static void Ui::Geo::funcName(DWORD color, Point<float>[] vertex, int num);
		static void Ui::Geo::funcName(DWORD color, std::vector<Point<float>> vertex);
		static void Ui::Geo::funcName(DWORD color, std::array<Point<float>, len> vertex);
		static void Ui::Geo::funcName(DWORD color, std::initializer_list<Point<float>> vertex);
		```
	- 根据给出的坐标序列及色彩函数进行绘制：
		```
		static void Ui::Geo::funcName(std::function<DWORD(float, float)> color, Point<float>[] vertex, int num);
		static void Ui::Geo::funcName(std::function<DWORD(float, float)> color, std::vector<Point<float>> vertex);
		static void Ui::Geo::funcName(std::function<DWORD(float, float)> color, std::array<Point<float>, len> vertex);
		static void Ui::Geo::funcName(std::function<DWORD(float, float)> color, std::initializer_list<Point<float>> vertex);
		```
	可选的funcName包括：
	- 绘制点序列：
		```
		Ui::Geo::PointList(...);
		```
	- 绘制线段序列，使用的顶点序列为：{0, 1}, {2, 3}, {4, 5}, ...：
		```
		Ui::Geo::LineList(...);
		```
	- 绘制连续折线，使用的顶点序列为：{0, 1}, {1, 2}, {2, 3}, ...：
		```
		Ui::Geo::LineTrip(...);
		```
	- 绘制三角形序列，使用的顶点序列为：{0, 1, 2}, {3, 4, 5}, {6, 7, 8}, ...：
		```
		Ui::Geo::TriangleList(...);
		```
	- 绘制连续三角形，使用的顶点序列为：{0, 1, 2}, {1, 2, 3}, {2, 3, 4}, ...：
		```
		Ui::Geo::TriangleTrip(...);
		```
	- 绘制连续三角形，使用的顶点序列为：{0, 1, 2}, {0, 2, 3}, {0, 3, 4}, ...：
		```
		Ui::Geo::TriangleFan(...);
		```
### <font color="#90c000">SharedImage接口</font>
- #### <font color="#30a0a0">Ui::SharedImage</font>
	使用引用计数的图像类
	- 构造空图像、使用ARGB像素序列构造图像、使用Pvz::DDImage对象构造图像：
		```
		Ui::SharedImage();
		Ui::SharedImage(int w, int h, DWORD* bits);
		Ui::SharedImage(Pvz::DDImage* img);
		```
	- 复制自身，但使用独立的引用计数：
		```
		Ui::SharedImage Ui::SharedImage::MakeBranch();
		```
	- 将自身使用的引用计数器独立：
		```
		Ui::SharedImage& Ui::SharedImage::Branch();
		```
	- 获取内部包装的Pvz::DDImage对象：
		```
		Pvz::DDImage* Ui::SharedImage::Image();
		Pvz::DDImage* Ui::SharedImage::operator->();
		Pvz::DDImage& Ui::SharedImage::operator*();
		Ui::SharedImage::operator Pvz::DDImage*();
		```
	- 绘制：
		```
		void Ui::SharedImage::Draw(DWORD theColor, Rect theSrcRect, Matrix3 theTransform, bool mix, Rect theDestRect);
		```
	- 通过路径构造/向路径写入图片，支持jpg/png/bmp格式：
		```
		Ui::SharedImage(std::string path);
		bool Ui::SharedImage::Write(std::string path);
		```
	- 截屏：
		```
		static Ui::SharedImage Ui::SharedImage::TakeScreenShot();
		```
	- 从剪贴板获取/向剪贴板保持图片：
		```
		static Ui::SharedImage Ui::SharedImage::GetClipBoard();
		void Ui::SharedImage::SetClipBoard();
		```
- #### <font color="#30a0a0">Pvz::DDImage</font>
	pvz内部的图像类：
	- 绘制
		```
		void Pvz::DDImage::Draw(DWORD color, Rect srcRect, Matrix3 transform, bool mix, Rect destRect);
		```
	- pvz内部资源文件：
		```
		Pvz::DDImage* Pvz::IMAGE_xxx;
		```
	- 例：
		```
		Pvz::DDImage* Pvz::IMAGE_PVZ_LOGO;
		```
### <font color="#90c000">Font接口</font>
- #### <font color="#30a0a0">Ui::Font</font>
	字体类
	- 创建字体：
		```
		Ui::Font(char* name, int pointSize, int gap, int script, int weight, bool italics, bool underline, bool deviceCaps);
		```
	- 生成文字对应的图像：
		```
		Ui::SharedImage Ui::Font::MakeImage(wchar_t chr);
		Ui::SharedImage Ui::Font::MakeImage(std::string_view str, int w);
		Ui::SharedImage Ui::Font::MakeImage(std::wstring_view str, int w);
		```
	- 绘制文字：
		```
		void Ui::Font::DrawString(int x, int y, std::string_view str, DWORD color, int w, int h);
		void Ui::Font::DrawString(int x, int y, std::wstring_view str, DWORD color, int w, int h);
		```
	- 绘制ascii文字，可略微提升性能：
		```
		void Ui::Font::DrawStringA(int x, int y, std::string_view str, DWORD color, int w, int h);
		```
	- 获取文字绘制所需空间参数：
		```
		int Ui::Font::GetStringWidth(std::string_view str);
		int Ui::Font::GetStringWidth(std::wstring_view str);
		int Ui::Font::GetStringLine(std::string_view str, int w);
		int Ui::Font::GetStringLine(std::wstring_view str, int w);
		int Ui::Font::GetStringHeight(std::string_view str, int w);
		int Ui::Font::GetStringHeight(std::wstring_view str, int w);
		```
- #### <font color="#30a0a0">Ui::Font& Ui::GlobalFont()</font>
	获取全局字体，可对其赋值以改变全局字体
### <font color="#90c000">Style接口</font>
- #### <font color="#30a0a0">Ui::Style</font>
	控件风格类：
	```
	struct Style {
		DWORD BaseColor;//背景色彩
		DWORD LineColor;//线条色彩
		DWORD LightColor;//淡化背景色彩
		DWORD LightLineColor;//淡化线条色彩
		DWORD SelectColor;//焦点背景色彩
		DWORD SelectLineColor;//焦点线条色彩
		float MixRate;//混合比，在混合产生衍生色彩时原色的权重，取值[0, 1]
	};
	```
- #### <font color="#30a0a0">Ui::Style& Ui::GlobalStyle()</font>
	获取全局控件风格，可对其赋值以改变全局控件风格
### <font color="#90c000">Command接口</font>
- #### <font color="#30a0a0">Cvp::UPCommand</font>
	命令类
	- 创建命令树:
		```
		Cvp::UPCommand Ui::MakeCmd(std::string_view command);
		Cvp::UPCommand Ui::MakeCmd(std::string_view command, argT...);//创建后使用operator()依次调用所有额外参数
		```
	- 为命令树设置激活条件，不设则始终激活:
		```
		Cvp::UPCommand Cvp::UPCommand::operator()(std::function<bool(void)>);
		```
	- 为命令树设置执行操作，不设则该命令仅作为分支使用:
		```
		Cvp::UPCommand Cvp::UPCommand::operator()(std::function<std::string(argT...)>);
		Cvp::UPCommand Cvp::UPCommand::operator()(std::function<void(argT...)>);
		```
	- 为命令树设置子树，不设则该命令仅作为执行命令使用:
		```
		Cvp::UPCommand Cvp::UPCommand::operator()(std::initializer_list<UPCommand>);
		Cvp::UPCommand Cvp::UPCommand::operator()(UPCommand);
		```
	- 依次使用多个参数调用operator():
		```
		Cvp::UPCommand Cvp::UPCommand::operator()(argT...);
		```
	- 添加全局命令：
		```
		static void Ui::WidgetManager::SetCmd(std::initializer_list<Cvp::UPCommand>);
		```
	<font color="#ff4040"><font size=5>注意：以上任何方法对UPCommand对象都是破坏性的，包括拷贝，不要对this对象和传入对象进行任何假设，只有返回值仍然将是合法的、符合预期的UPCommand对象</font></font>
	- 调用全局命令：
		```
		string Ui::CallCmd(string_view cmd);//仅支持ascii，非打印字符会被剔除
		```
	- 例：
		```
		Ui::WidgetManager::SetCmd({
			Ui::MakeCmd(u8"system")//顶级命令
			([]()->bool{ return Pvz::gGameApp; })//激活条件
			(//子命令
				Ui::MakeCmd(u8"TakeScreenShot")//二级命令
				([](string_view path)->string{ return Ui::SharedImage::TakeScreenShot().Write(path) ? u8"succeed" : u8"failed"; })//执行操作
				,
				Ui::MakeCmd(u8"ShutDown")//二级命令
				([](){ *(char*)0x0ul=u8'!'; })//执行操作
			),
		});

		Ui::CallCmd(u8"system TakeScreenShot C:\\");//截图并保存至C盘
		```
### <font color="#90c000">Widget接口</font>
- #### <font color="#30a0a0">Ui::WidgetBase</font>
	cvp控件公共基类
	- 移动控件，零点为父窗体的左上角：
		```
		void Ui::WidgetBase::Move(int dx, int dy);
		void Ui::WidgetBase::MoveTo(int x, int y);
		```
	- 设置父/子窗体，只需从一个方向调用即可：
		```
		void Ui::WidgetBase::SetParent(Ui::WidgetBase*);
		int Ui::WidgetBase::AddChildren(std::initializer_list<Ui::WidgetBase*>);
		```
	- 设置/获取控件状态：
		```
		void Ui::WidgetBase::SetInvisible(bool);
		void Ui::WidgetBase::SetInactive(bool);
		void Ui::WidgetBase::SetClosed();
		void Ui::WidgetBase::SetFocus(bool);
		bool Ui::WidgetBase::GetInvisible()const;
		bool Ui::WidgetBase::GetInactive()const;
		bool Ui::WidgetBase::GetClosed()const;
		bool Ui::WidgetBase::GetFocus()const;
		```
	- 获取控件空间参数：
		```
		int Ui::WidgetBase::GetX()const;
		int Ui::WidgetBase::GetY()const;
		int Ui::WidgetBase::GetW()const;
		int Ui::WidgetBase::GetH()const;
		```
	- 获取父/子窗体：
		```
		WidgetBase* Ui::WidgetBase::GetParent()const;
		std::vector<Ui::WidgetBase*>& Ui::WidgetBase::GetChildren()const;
		```
	- 是否被鼠标悬浮/被按下：
		```
		bool Ui::WidgetBase::GetOver()const;
		bool Ui::WidgetBase::GetDown()const;
		```
	- 弹出模态窗口，实际由父窗口执行：
		```
		void Ui::WidgetBase::DoModal(Ui::Widget*);
		```
- #### <font color="#30a0a0">Ui::Widget</font>
	<font color="#ff4040">Ui::WidgetBase的派生类</font>，窗口类，窗体调度的基本单位,
	- 弹出模态窗口：
		```
		void Ui::WidgetBase::DoModal(Ui::Widget*);
		```
	- 获取模态窗口：
		```
		Ui::Widget* Ui::WidgetBase::GetModal();
		```
	- 加入窗口管理器，建议使用Title对象完成此步骤：
		```
		void Ui::Widget::AttachManager();
		```
	- 加入控制页，不建议使用Title对象完成此步骤：
		```
		void Ui::Widget::AttachTab(std::string_view label);
		```
- #### <font color="#30a0a0">Ui::Invisible</font>
	<font color="#ff4040">Ui::Widget的派生类</font>，Ui::WidgetBase到Ui::Widget的适配器，创建完全透明的窗口以容纳控件
	- 构造透明窗口：
		```
		Ui::Invisible(Ui::WidgetBase*);
		```
- #### <font color="#30a0a0">Ui::WidgetManager</font>
	窗口管理器
	- 创建基础窗口：
		```
		static Ui::Widget* Ui::WidgetManager::MakeWidget(Rect rect, std::initializer_list<Ui::WidgetBase*> children);
		```
	- 创建标准尺寸的窗口，用于控制页：
		```
		static Ui::Widget* Ui::WidgetManager::MakeTabPage(std::initializer_list<Ui::WidgetBase*> children);
		```
	- 创建窗口，附加可拖动且带有关闭按钮的标题栏：
		```
		static Ui::Widget* Ui::WidgetManager::MakeTitle(std::string_view title, Ui::Widget* body, SharedImage icon);
		```
	- 创建标签：
		```
		static Ui::WidgetBase* Ui::WidgetManager::MakeLabel(Rect rect, std::string_view label);
		```
	- 创建文字输出：
		```
		static Ui::WidgetBase* Ui::WidgetManager::MakeOutput(Rect rect, std::string str);
		static Ui::WidgetBase* Ui::WidgetManager::MakeOutput(Rect rect, std::wstring str);
		```
	- 创建按钮：
		```
		static Ui::WidgetBase* Ui::WidgetManager::MakeButton(Rect rect, std::function<void(void)> func, std::string_view label);
		```
	- 创建按键选择器：
		```
		static Ui::WidgetBase* Ui::WidgetManager::MakeKeySelector(Point<int> pos, std::function<void(Cvp::KeyCode)> func, Cvp::KeyCode _default);
		static Ui::WidgetBase* Ui::WidgetManager::MakeKeySelector(Point<int> pos, Cvp::KeyCode& link);
		```
	- 创建输入：
		```
		static Ui::WidgetBase* Ui::WidgetManager::MakeInput(Rect rect, std::function<void(std::string_view)> func, std::string_view _default);
		static Ui::WidgetBase* Ui::WidgetManager::MakeInput(Rect rect, std::function<void(int)> func, int _default);
		static Ui::WidgetBase* Ui::WidgetManager::MakeInput(Rect rect, std::function<void(float)> func, float _default);
		static Ui::WidgetBase* Ui::WidgetManager::MakeInput(Rect rect, std::string& link);
		static Ui::WidgetBase* Ui::WidgetManager::MakeInput(Rect rect, int& link);
		static Ui::WidgetBase* Ui::WidgetManager::MakeInput(Rect rect, float& link);
		```
	- 创建水平/垂直滑动条：
		```
		static Ui::WidgetBase* Ui::WidgetManager::MakeSlider_H(Rect rect, std::function<void(float)> func, int gap, float Min, float Max, float _default);
		static Ui::WidgetBase* Ui::WidgetManager::MakeSlider_H(Rect rect, std::function<void(float)> func, int gap, float Min, float Max);
		static Ui::WidgetBase* Ui::WidgetManager::MakeSlider_H(Rect rect, std::function<void(float)> func, int gap, float Max);
		static Ui::WidgetBase* Ui::WidgetManager::MakeSlider_H(Rect rect, float& link, int gap, float Min, float Max);
		static Ui::WidgetBase* Ui::WidgetManager::MakeSlider_H(Rect rect, float& link, int gap, float Max);
		static Ui::WidgetBase* Ui::WidgetManager::MakeSlider_V(Rect rect, std::function<void(float)>& func, int gap, float Min, float Max, float _default);
		static Ui::WidgetBase* Ui::WidgetManager::MakeSlider_V(Rect rect, std::function<void(float)> func, int gap, float Min, float Max);
		static Ui::WidgetBase* Ui::WidgetManager::MakeSlider_V(Rect rect, std::function<void(float)> func, int gap, float Max);
		static Ui::WidgetBase* Ui::WidgetManager::MakeSlider_V(Rect rect, float& link, int gap, float Min, float Max);
		static Ui::WidgetBase* Ui::WidgetManager::MakeSlider_V(Rect rect, float& link, int gap, float Max);
		```
	- 创建复选框：
		```
		static Ui::WidgetBase* Ui::WidgetManager::MakeCheck(Rect rect, std::function<void(bool)> func, std::string_view label, bool _default);
		static Ui::WidgetBase* Ui::WidgetManager::MakeCheck(Rect rect, bool& link, std::string_view label);
		```
	- 创建单选框组：
		```
		static Ui::WidgetBase* Ui::WidgetManager::MakeRadio(Rect rect, std::initializer_list<std::pair<Rect, std::string_view>> children, std::function<void(int)> func, int _default, std::string_view label);
		static Ui::WidgetBase* Ui::WidgetManager::MakeRadio(Rect rect, std::initializer_list<tuple<Rect, std::function<void(bool)>, std::string_view>> children, int _default, std::string_view label);
		static Ui::WidgetBase* Ui::WidgetManager::MakeRadio(Rect rect, std::initializer_list<std::pair<Rect, std::string_view>> children, int& link, int _default, std::string_view label);
		static Ui::WidgetBase* Ui::WidgetManager::MakeRadio(Rect rect, std::initializer_list<tuple<Rect, bool* const, std::string_view>> children, int _default, std::string_view label);
		```
	- 创建下拉框：
		```
		static Ui::WidgetBase* Ui::WidgetManager::MakeComboList(Rect rect, std::initializer_list<std::string_view> elements, std::function<void(int)> func, int _default);
		static Ui::WidgetBase* Ui::WidgetManager::MakeComboList(Rect rect, std::initializer_list<std::pair<std::string_view, std::function<void(bool)>>> elements, int _default);
		static Ui::WidgetBase* Ui::WidgetManager::MakeComboList(Rect rect, std::initializer_list<std::string_view> elements, int& link, int _default);
		static Ui::WidgetBase* Ui::WidgetManager::MakeComboList(Rect rect, std::initializer_list<std::pair<std::string_view, bool*>> elements, int _default);
		```
	- 添加窗口：
		```
		static void Ui::WidgetManager::AddWidget(Ui::Widget* widget);
		```
	- 设置/取消某一窗口的焦点：
		```
		static void Ui::WidgetManager::FocusWidget(Ui::WidgetBase* widget);
		static void Ui::WidgetManager::ReleaseWidget(Ui::WidgetBase* widget);
		```
	- 添加控制页：
		```
		static void Ui::WidgetManager::SetTab(std::initializer_list<std::pair<std::string_view, Ui::Widget*>> page);
		```
	- 添加命令：
		```
		static void Ui::WidgetManager::SetCmd(std::initializer_list<Cvp::UPCommand> cmd);
		```
	- 获取按键状态：
		```
		static bool Ui::WidgetManager::Shift();
		static bool Ui::WidgetManager::Ctrl();
		static bool Ui::WidgetManager::Alt();
		```
## DeriveManager数据库（部分启用）
### <font color="#90c000">TypeInteface接口</font>
- #### <font color="#30a0a0">Cvp::TypeTrait\<T\></font>
	- 数据库元信息：
		```
		struct Cvp::TypeTrait<T> {
			using type = typename T::Type;//记录多态类型索引，特例化时需包含ENM_BEGIN表示希望预留区域的大小
			enum class prop :DWORD {//记录类属性偏移
				 CONSTRUCT = sizeof(Cvp::Functor<void(void)>) * 0,
				 DESTRUCT = sizeof(Cvp::Functor<void(void)>) * 1,
				 SERIALIZE = sizeof(Cvp::Functor<void(void)>) * 2,
				 DESERIALIZE = sizeof(Cvp::Functor<void(void)>) * 3,
				 PROP_BEGIN = sizeof(Cvp::Functor<void(void)>) * 4
			};
		};
		```
- #### <font color="#30a0a0">Cvp::TypeInterface\<T\></font>
	类型属性数据库类型池接口，存储、控制及交互跨模块动态类型信息
	- 构造接口，除name外参数可选，使用_default参数时需特例化Cvp::TypeTrait<T>：
		```
		Cvp::TypeInterface(string name, std::function<void(Cvp::TypeInterface*)> datainit, DeriveType _default);
		```
	<font color="#ff4040"><font size=5>注意：若传入参数仅包含name且可以接受接口构造失败，则允许构造局部接口对象，否则接口必须构造为全局对象</font></font>
	- 内置类型，用于记录类型索引、属性偏移，不推荐显式使用：
		```
		using Cvp::TypeInterface::DeriveType = Cvp::TypeTrait<T>::type;
		using Cvp::TypeInterface::PropType = Cvp::TypeTrait<T>::prop;
		```
	- 获取内置类型索引，不推荐使用：
		```
		Cvp::TypeInterface::DeriveType Type()const;
		```
	- 设置类型属性信息，数据库构建者可于构造函数datainit参数内调用，修改者可于Pvz::MainLoopHook接口内调用：
		```
		fieldT& Cvp::TypeInterface::Set(Cvp::PropInterface<T, fieldT>, ...)const;
		```
	- 获取类型属性信息：
		```
		fieldT& Cvp::TypeInterface::operator[](Cvp::PropInterface<T, fieldT>)const;
		fieldT& Cvp::TypeInterface::Get(Cvp::PropInterface<T, fieldT>)const;
		```
### <font color="#90c000">PropInteface接口</font>
- #### <font color="#30a0a0">Cvp::PropInteface\<T, fieldT\></font>
	类型属性数据库属性池接口，存储、控制及交互跨模块动态类型属性信息
	- 构造接口，除name外参数可选：	
		```
		Cvp::PropInterface(string name, std::function<void(Cvp::PropInterface<T, fieldT>*)> datainit);
		```
	<font color="#ff4040"><font size=5>注意：接口必须构造为全局对象</font></font>
	- 内置类型，用于记录类型索引、属性偏移，不推荐显式使用：
		```
		using Cvp::PropInterface::DeriveType = Cvp::TypeTrait<T>::type;
		using Cvp::PropInterface::PropType = Cvp::TypeTrait<T>::prop;
		```
	- 获取内置属性偏移，不推荐使用：
		```
		Cvp::PropInterface::PropType Prop()const;
		```
	- 设置类型属性信息，数据库构建者可于构造函数datainit参数内调用，修改者可于Pvz::MainLoopHook接口内调用：
		```
		fieldT& Cvp::PropInterface::Set(Cvp::PropInterface::DeriveType, ...)const;
		fieldT& Cvp::PropInterface::Set(Cvp::TypeInterface<T>, ...)const;
		void Cvp::PropInterface::SetAll(...)const;
		fieldT& Cvp::PropInterface::SetDefault(...)const;
		```
	- 获取类型属性信息：
		```
		fieldT& Cvp::PropInterface::operator[](Cvp::PropInterface::DeriveType)const;
		fieldT& Cvp::PropInterface::operator[](Cvp::TypeInterface<T>)const;
		fieldT& Cvp::PropInterface::Get(Cvp::PropInterface::DeriveType)const;
		fieldT& Cvp::PropInterface::Get(Cvp::TypeInterface<T>)const;
		```
	- 类型属性迭代器：
		```
		Cvp::PropInterface::iterator Cvp::PropInterface::begin()const;
		Cvp::PropInterface::iterator Cvp::PropInterface::end()const;
		```
## ObjectManager数据库（未启用）
### <font color="#90c000">ObjectInteface接口</font>
- #### <font color="#30a0a0">Cvp::TypeTrait\<T\></font>
	- 数据库元信息：
		```
		struct Cvp::TypeTrait<T> {
			enum class pool :DWORD { DEFAULT, POOL_BEGIN };//记录对象池索引，特例化时需包含POOL_BEGIN表示希望预留区域的大小
			enum class member :DWORD;//记录对象成员偏移
		};
		```
- #### <font color="#30a0a0">Cvp::ObjectInteface\<T\></font>
	对象成员数据库对象池接口，存储、控制及交互跨模块多态对象信息
	- 构造接口，除name外参数可选，使用_default参数时需特例化Cvp::TypeTrait<T>：
		```
		Cvp::ObjectInterface(string name, PoolType _default);
		```
	<font color="#ff4040"><font size=5>注意：接口必须构造为全局对象</font></font>
	- 内置类型，用于记录类型索引、属性偏移、对象池索引、成员偏移，不推荐显式使用：
		```
		using Cvp::ObjectInterface::DeriveType = Cvp::TypeTrait<T>::type;
		using Cvp::ObjectInterface::PropType = Cvp::TypeTrait<T>::prop;
		using Cvp::ObjectInterface::PoolType = Cvp::TypeTrait<T>::pool;
		using Cvp::ObjectInterface::MemberType = Cvp::TypeTrait<T>::member;
		```
	- 内置类型，用于表示对象所占内存空间：
		```
		Cvp::ObjectInterface::Object;
		```
	- 内置类型，用于表示对象本身：
		```
		Cvp::ObjectInterface::ID;
		```
	- 获取内置对象池索引，不推荐使用：
		```
		Cvp::ObjectInterface::PoolType Cvp::ObjectInterface::Pool()const;
		```
	- 从对象池中申请内存：
		```
		Cvp::ObjectInterface::Object& Cvp::ObjectInterface::Alloc(Cvp::ObjectInterface::DeriveType);
		Cvp::ObjectInterface::Object& Cvp::ObjectInterface::Alloc(Cvp::TypeInterface<T>);
		```
	- 释放对象池内存单元：
		```
		void Cvp::ObjectInterface::Free(Cvp::ObjectInterface::Object&&);
		void Cvp::ObjectInterface::Free(Cvp::ObjectInterface::ID);
		```
	- 在指定内存单元构造对象：
		```
		static Cvp::ObjectInterface::Object& Cvp::ObjectInterface::Construct(Cvp::ObjectInterface::Object&);
		void Cvp::ObjectInterface::Construct(Cvp::ObjectInterface::ID);
		```
	- 析构对象：
		```
		static void Cvp::ObjectInterface::Destruct(Cvp::ObjectInterface::Object&);
		void Cvp::ObjectInterface::Destruct(Cvp::ObjectInterface::ID);
		```
	- 从对象池申请内存并构造对象：
		```
		Cvp::ObjectInterface::Object& Cvp::ObjectInterface::New(Cvp::ObjectInterface::DeriveType);
		Cvp::ObjectInterface::Object& Cvp::ObjectInterface::New(Cvp::ObjectInterface::TypeInterface<T>);
		```
	- 析构对象并释放内存：
		```
		static void Cvp::ObjectInterface::Delete(Cvp::ObjectInterface::Object&&);
		void Cvp::ObjectInterface::Delete(Cvp::ObjectInterface::ID);
		```
	- 清空对象池：
		```
		void Cvp::ObjectInterface::Clear();
		```
	- 将指定对象序列化：
		```
		static Cvp::DataBase Cvp::ObjectInterface::Serialize(Cvp::ObjectInterface::Object&);
		Cvp::DataBase Cvp::ObjectInterface::Serialize(Cvp::ObjectInterface::ID)const;
		```
	- 反序列化至指定对象：
		```
		static void Cvp::ObjectInterface::Deserialize(Cvp::ObjectInterface::Object&, Cvp::DataBase&& buffer);
		void Cvp::ObjectInterface::Deserialize(Cvp::ObjectInterface::ID, Cvp::DataBase&& buffer);
		```
	- 序列化/反序列化对象池：
		```
		Cvp::DataBase Cvp::ObjectInterface::Serialize()const;
		void Cvp::ObjectInterface::Deserialize(Cvp::DataBase&& data);
		```
	- 根据ID尝试获取对象：
		```
		Cvp::ObjectInterface::Object* Cvp::ObjectInterface::Get(Cvp::ObjectInterface::ID)const;
		```
	- 对象迭代器：
		```
		Cvp::ObjectInterface::iterator Cvp::ObjectInterface::begin()const;
		Cvp::ObjectInterface::iterator Cvp::ObjectInterface::end()const;
		```
### <font color="#90c000">Object接口</font>
- #### <font color="#30a0a0">Cvp::ObjectInterface\<T\>::Object</font>
	动态多态对象接口
	- 获取对象成员
		```
		fieldT& Cvp::ObjectInterface<T>::Object::operator[](Cvp::MemberInterface<T, fieldT>)const;
		fieldT& Cvp::ObjectInterface<T>::Object::Get<fieldT>(Cvp::ObjectInterface<T>::MemberType)const;
		```
	- 获取对象ID及类型
		```
		Cvp::ObjectInterface<T>::ID Cvp::ObjectInterface<T>::Object::GetID();
		Cvp::ObjectInterface<T>::DeriveType& Cvp::ObjectInterface<T>::Object::GetType()const;
		```
	- 释放对象内存/析构对象
		```
		void Cvp::ObjectInterface<T>::Object::Free();
		void Cvp::ObjectInterface<T>::Object::Delete();
		```
	- 序列化/反序列化对象
		```
		DataBase Cvp::ObjectInterface<T>::Object::Serialize();
		void Cvp::ObjectInterface<T>::Object::Deserialize(DataBase&& buffer);
		```
### <font color="#90c000">MemberInteface接口</font>
- #### <font color="#30a0a0">Cvp::MemberInteface\<T, fieldT\></font>
	对象成员数据库成员池接口，存储、控制及交互跨模块多态对象成员信息
	- 构造接口，除name外参数可选：
		```
		Cvp::MemberInterface(string name, std::function<void(Cvp::MemberInterface<T, fieldT>*)> staticinit);
		```
	<font color="#ff4040"><font size=5>注意：接口必须构造为全局对象</font></font>
	- 内置类型，用于记录类型索引、属性偏移、对象池索引、成员偏移，不推荐显式使用：
		```
		using Cvp::MemberInterface::DeriveType = Cvp::TypeTrait<T>::type;
		using Cvp::MemberInterface::PropType = Cvp::TypeTrait<T>::prop;
		using Cvp::MemberInterface::PoolType = Cvp::TypeTrait<T>::pool;
		using Cvp::MemberInterface::MemberType = Cvp::TypeTrait<T>::member;
		```
	- 获取内置成员偏移，不推荐使用：
		```
		Cvp::MemberInterface::MemberType Cvp::MemberInterface::Member()const;
		```
	- 获取对象成员
		```
		fieldT& Cvp::MemberInterface::operator[](Cvp::ObjectInterface<T>::Object&)const;
		```
	- 设置某一类型中本接口对应成员的构造函数/析构函数/序列化与反序列化函数
		```
		void Cvp::MemberInterface::Set_Constructor(Cvp::MemberInterface::DeriveType type, std::function<void(fieldT&)> func);
		void Cvp::MemberInterface::Set_Destructor(Cvp::MemberInterface::DeriveType type, std::function<void(fieldT&)> func);
		void Cvp::MemberInterface::Set_Serializer(Cvp::MemberInterface::DeriveType type, std::function<void(fieldT&, Data&)> func_serialize, std::function<void(FieldT&, Data&)> func_deserialize);
		void Cvp::MemberInterface::Set_Serializer(Cvp::MemberInterface::DeriveType type, std::function<void(fieldT&, Data&)> func);
		void Cvp::MemberInterface::Set_Constructor(Cvp::TypeInterface<T> type, std::function<void(fieldT&)> func);
		void Cvp::MemberInterface::Set_Destructor(Cvp::TypeInterface<T> type, std::function<void(fieldT&)> func);
		void Cvp::MemberInterface::Set_Serializer(Cvp::TypeInterface<T> type, std::function<void(fieldT&, Data&)> func_serialize, std::function<void(FieldT&, Data&)> func_deserialize);
		void Cvp::MemberInterface::Set_Serializer(Cvp::TypeInterface<T> type, std::function<void(fieldT&, Data&)> func);
		```
	- 设置部分类型中本接口对应成员的构造函数/析构函数/序列化与反序列化函数
		```
		void Cvp::MemberInterface::Set_Constructor(std::function<void(fieldT&)> func, std::function<bool(Cvp::MemberInterface::DeriveType)> range);
		void Cvp::MemberInterface::Set_Destructor(std::function<void(fieldT&)> func, std::function<bool(Cvp::MemberInterface::DeriveType)> range);
		void Cvp::MemberInterface::Set_Serializer(std::function<void(fieldT&, Data&)> func_serialize, std::function<void(fieldT&, Data&)> func_deserialize, std::function<bool(Cvp::MemberInterface::DeriveType)> range);
		void Cvp::MemberInterface::Set_Serializer(std::function<void(fieldT&, Data&)> func, std::function<bool(Cvp::MemberInterface::DeriveType)> range);
		```
	- 根据类型设置本接口对应成员的构造函数/析构函数/序列化与反序列化函数
		```
		void Set_Constructor(std::function<std::function<void(FieldT&)>(DeriveType)> func_factory);
		void Set_Destructor(std::function<std::function<void(FieldT&)>(DeriveType)> func_factory);
		void Set_Serializer(std::function<std::function<void(FieldT&, Data&)>(DeriveType)> func_factory_serialize, std::function<std::function<void(FieldT&, Data&)>(DeriveType)> func_factory_deserialize);
		void Set_Serializer(std::function<std::function<void(FieldT&, Data&)>(DeriveType)> func_factory);
		```
	- 设置全部类型中本接口对应成员的构造函数/析构函数/序列化与反序列化函数
		```
		void Cvp::MemberInterface::Set_Constructor(std::function<void(fieldT&)> func);
		void Cvp::MemberInterface::Set_Destructor(std::function<void(fieldT&)> func);
		void Cvp::MemberInterface::Set_Serializer(std::function<void(fieldT&, Data&)> func_serialize, std::function<void(fieldT&, Data&)> func_deserialize);
		void Cvp::MemberInterface::Set_Serializer(std::function<void(fieldT&, Data&)> func);
		```
	- 尝试对所有类型中本接口对应成员设置默认构造函数/析构函数/序列化与反序列化函数
		```
		void Cvp::MemberInterface::Set_Constructor();
		void Cvp::MemberInterface::Set_Destructor();
		void Cvp::MemberInterface::Set_Serializer();
		```
	<font color="#ff4040"><font size=5>注意：永远不要在任何场合（同模块内/不同模块同时）重复设置构造函数、析构函数、序列化与反序列化函数</font></font>
## 杂项及补充
### <font color="#90c000">关于Functor对象</font>
- #### <font color="#30a0a0">Cvp::Functor\<retT(argT...)\></font>
	函数类，使用引用计数
	- 构造
		```
		Cvp::Functor<retT(argT...)>(std::function<retT(argT...)>);//产生函数
		Cvp::Functor<retT(argT...)>(retT);//产生常量函数
		Cvp::Functor<void(argT...)>();//产生空函数
		```
	- 分支
		```
		Cvp::Functor<retT(argT...)> Cvp::Functor::MakeBranch()const;//复制自身，但返回值使用独立的引用计数
		Cvp::Functor<retT(argT...)>& Cvp::Functor::Branch();//将自身使用的引用计数与其他对象独立
		```
	- 复合
		```
		Cvp::Functor<retT(argT...)>& Cvp::Functor::operator+=(std::function<retT(argT...)>);//将当前对象的operator()过程转为新的函数，原过程设为当前对象的上级函数
		```
	- 调用
		```
		retT Cvp::Functor::operator()(argT...)const;//调用当前函数
		static retT Cvp::Functor::Recur(argT...);//调用当前调用中对象的上级函数
		```
### <font color="#90c000">序列化与反序列化机制</font>
- #### <font color="#30a0a0">Cvp::Data</font>
	序列化数据元
	- 构造
		```
		Cvp::Data();
		```
	- 判定
		```
		bool Cvp::Data::isEmpty()const;//空
		bool Cvp::Data::isData()const;//数据
		bool Cvp::Data::isTree()const;//子树
		```
	- 断言
		```
		void Cvp::Data::checkEmpty()const;
		void Cvp::Data::checkNotEmpty()const;
		void Cvp::Data::checkData()const;
		void Cvp::Data::checkTree()const;
		```
	- 写入/读取数据
		```
		void Cvp::Data::Push(const T& val);//使用Template::serializeN<T>(const T*)和Template::serialize<T>(const T&, BYTE*)，自定义类型需重载这两个模板
		void Cvp::Data::Pop(T& val)const;//使用Template::deserialize<T>(Y&, BYTE*, int)，自定义类型需重载这个模板
		```
	- 写入/读取树
		```
		void Cvp::Data::SetChild(DataMap&& val);
		CvP::DataMap& Cvp::Data::GetChild()const;
		```
- #### <font color="#30a0a0">Cvp::DataMap</font>
	序列化树
	- 构造
		```
		Cvp::DataMap();//构造空树
		Cvp::DataMap(char* path);//从路径读取树
		```
	- 保存
		```
		void Cvp::DataMap::Write(char* path)const;//将树保存到对象
		```
	- 写入/读取
		```
		void Cvp::DataMap::Set(std::string label, Data&& data);//写入数据元
		Cvp::Data Cvp::DataMap::Get(std::string label)const;//获取数据元
		```
	- 迭代器
		```
		Cvp::DataMap::iterator Cvp::DataMap::begin()const;
		Cvp::DataMap::iterator Cvp::DataMap::end()const;
		```
### <font color="#90c000">工具接口</font>
# 介绍————to 加载器开发者
cvp vs. (plants vs. zombies)\
pvz的逻辑还原，以动态语言方式重新实现pvz逻辑并调用pvz自身二进制底层函数\
使用cvp编写加载器模块，可直接修改pvz运行逻辑，也可对外暴露设计的接口\
涉及文件：<font color="#50b0f0">pvzClass.h pvzStatic.h ui.h pvzData.h</font>
## 接口
# 介绍————to cvp开发者
cvp vs. (plants vs. zombies)\
使用模板元编程实现基于C++的高性能动态多态类型编程库\
涉及文件：<font color="#50b0f0">cvp.h dynamic_language.h Game.h</font>
## cvp项目结构
