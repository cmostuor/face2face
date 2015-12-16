#ifndef CameraH
#define CameraH

#include <QVector2D>
#include <QVector3D>
#include <QMatrix4x4>
#include <cmath>

class Sensor{
private:
	int px_w;
	int px_h;
	float px_size; //[µm]

public:
	Sensor() : px_w (1280), px_h(960), px_size(3.75f) {}
	Sensor(float w, float h, float px_s) : px_w(w), px_h(h), px_size(px_s){}
	~Sensor(){}

public:
	inline int getWidth() { return px_w; }
    inline int getWidth() const { return px_w; }
	inline void setWidth(const int w) { px_w = w; }
	
	inline int getHeight() { return px_h; }
    inline int getHeight() const { return px_h; }
	inline void setHeight(const int h) { px_h = h; }

	inline float getPixelSize() { return px_size; }
    inline float getPixelSize() const { return px_size; }
	inline void setPixelSize(const float s) { px_size = s; }

	inline const QVector2D getSensorSize() const { QVector2D s(px_w * px_size / 1000.0f, px_h * px_size / 1000.0f); return s; } //[mm]
};

class Lens{
private:
	float focal_distance; //[mm]
	float sensor_distance; //[mm]
	float f_number; // f/N
	float shutter_speed; //[ms]

public:
	Lens() : focal_distance(6.0f), sensor_distance(6.001f), f_number(2.5f), shutter_speed(40){}
	Lens(float f, float d, float N, float s) : focal_distance(f), sensor_distance(d), f_number(N), shutter_speed(s){}
	~Lens(){}

public:
	inline float getFocalDistance() { return focal_distance; }
    inline float getFocalDistance() const { return focal_distance; }
	inline void setFocalDistance(float f) { focal_distance = f; }

	inline float getSensorDistance() { return sensor_distance; }
    inline float getSensorDistance() const { return sensor_distance; }
	inline void setSensorDistance(float d) { sensor_distance = d; }

	inline float getFNum() { return f_number; }
    inline float getFNum() const { return f_number; }
	inline void setFNum(float N) { f_number = N; }

	inline float getShutterSpeed(){ return shutter_speed; }
    inline float getShutterSpeed() const { return shutter_speed; }
	inline void setShutterSpeed(float s){ shutter_speed = s; }
};

class Camera{
public:
	Camera();
	Camera(float near, float far);
	~Camera();

private:
	//Sensor
	Sensor* sensor;
	//Lens
	Lens* lens;

	/* OPENGL properties */
	//OGL near plane
	float near_plane;
	//OGL far plane
	float far_plane;
	//OGL eye point
	QVector3D eye;
	//OGL lookat point
	QVector3D center;
	//OGL up vector
	QVector3D up;
	//OGL projection matrix
	QMatrix4x4 proj_mat;
	//OGL view matrix
	QMatrix4x4 view_mat;

public:
	//Const sensor getter
	inline const Sensor* getSensor(){ return sensor; }
	//Const lens getter
	inline const Lens* getLens(){ return lens; }

	//Returns near plane z-coordinate in frustum coordinates
    inline float getNearPlane() { return near_plane; }
	//Returns the near plane z-coordinate in eye space
    inline float getEyeNearPlane() { QVector3D line_of_sight = center - eye; float np = (eye + line_of_sight * near_plane).z(); return np; }

	//Returns far plane z-Coordinate in frustum coordinates
    inline float getFarPlane() { return far_plane; }
	//Returns the far plane z-coordinate in eye space
    inline float getEyeFarPlane() { QVector3D line_of_sight = center - eye; float fp = (eye + line_of_sight * far_plane).z(); return fp; }

	//Set near plane z-coordinate
	inline void setNearPlane(float n) { near_plane = n; updateProjectionMatrix(); }
	//Set far plane z-coordinate
	inline void setFarPlane(float f) { far_plane = f; updateProjectionMatrix(); }

	//Get field of view in y-direction
	inline float getFovy() { float d = sensor->getSensorSize()[1]; float f = lens->getFocalDistance(); float a = 2 * atanf(d / (2 * f)); return radToDeg(a); }
	//Get aspect ratio
	inline float getAspectRatio() { return sensor->getWidth() / (float)sensor->getHeight(); }
	
	//Get eye point
    inline QVector3D& getEye() { return eye; }
	//get lookat point
    inline QVector3D& getCenter() { return center; }
	//Get up vector
    inline QVector3D& getUp() { return up; }

	//Set eye point
	inline void setEye(QVector3D& e) { eye = e; updateViewMatrix(); }
	//Set lookat point
	inline void setCenter(QVector3D& c) { center = c; updateViewMatrix(); }
	//Set up vector
	inline void setUp(QVector3D& u) { up = u; updateViewMatrix(); }

	//Get OGL projection matrix
    inline QMatrix4x4& getProjMatrix() { return proj_mat; }
	//Get OGL view matrix
    inline QMatrix4x4& getViewMatrix() { return view_mat; }

	/* Sensor wrapping methods */
	//Set sensor width in pixels
	inline void setSensorWidth(const int w) { sensor->setWidth(w); updateProjectionMatrix(); }
	//Set sensor height in pixels
	inline void setSensorHeight(const int h) { sensor->setHeight(h); updateProjectionMatrix(); }
	//Set sensor pixel size in µm
	inline void setSensorPixelSize(const float s) { sensor->setPixelSize(s); }

	/* Lens wrapping methods */
	//Set lens focal distance in mm
	inline void setLensFocalDistance(const float f){ lens->setFocalDistance(f); updateProjectionMatrix(); }
	//Set lens sensor distance in mm
	inline void setLensSensorDistance(const float d){ lens->setSensorDistance(d); }
	//Set lens f-number (aperture)
	inline void setLensFNum(const float N){ lens->setFNum(N); }
	//Set lens shutter speed in ms
	inline void setLensShutterSpeed(const float s){ lens->setShutterSpeed(s); }

	//Returns dimensions of plane with specified z-coordinate in viewing volume
	void getPlaneDimensions(float z, QVector3D& top_left, QVector3D& bottom_right);

	//Get focussed distance
	float getFocussedDistance(); //[mm]

	//Calculate circle of confusion of plane with depth d on the sensor
	float calcCoC(float d); //[px]

	//Helper functions
    static float degToRad(const float angle) { return angle * M_PI / 180.0f; }
    static float radToDeg(const float angle) { return angle / M_PI * 180.0f; }

private:
	//Update OGL projection matrix
	void updateProjectionMatrix();
	//Update OGL view matrix
	void updateViewMatrix();
};

#endif
