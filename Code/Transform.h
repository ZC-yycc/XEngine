#ifndef TRANSFORM_H
#define TRANSFORM_H

/*
		变换组件
包含一个基础的Vector2类有x，y两个分量，以及一些数学运算
Transform负责物体的位置，旋转，缩放，计算模型矩阵，四元数和欧拉角呼唤
沟通opengl世界和物理世界
*/
#include <math.h>
#include "ThirdPartyLib/bullet/src/btBulletDynamicsCommon.h"
#include "XMath.h"

class XObject;

struct Vector2
{
	Vector2() {
		x_ = 0; y_ = 0;
	}
	Vector2(const float &x, const float &y) {
		x_ = x; y_ = y;
	}
	Vector2(const Vector2& vec2) {
		x_ = vec2.x_;
		y_ = vec2.y_;
	}
	Vector2(const Vector2* vec2) {
		x_ = vec2->x_;
		y_ = vec2->y_;
	}

//运算符重载
#if 1
	inline Vector2 operator=(const Vector2 &input) {
		this->x_ = input.x_;
		this->y_ = input.y_;
		return *this;
	}

	inline bool operator==(const Vector2 &input) const {
		return (this->x_ == input.x_ && this->y_ == input.y_);
	}

	inline bool operator!=(const Vector2 &input) const {
		return (this->x_ != input.x_ || this->y_ != input.y_);
	}

	inline Vector2 operator+(const Vector2 &input) const {
		Vector2 temp;
		temp.x_ = this->x_ + input.x_;
		temp.y_ = this->y_ + input.y_;
		return temp;
	}

	inline Vector2 operator-(const Vector2 &input) const {
		Vector2 temp;
		temp.x_ = this->x_ - input.x_;
		temp.y_ = this->y_ - input.y_;
		return temp;
	}

	inline Vector2 operator*(const float &multiple)const {
		Vector2 temp;
		temp.x_ = this->x_ * multiple;
		temp.y_ = this->y_ * multiple;
		return temp;
	}

	inline Vector2 operator*(const Vector2& input)const {
		Vector2 temp;
		temp.x_ = this->x_ * input.x_;
		temp.y_ = this->y_ * input.y_;
		return temp;
	}

	inline Vector2 operator/(const float &multiple)const {
		Vector2 temp;
		temp.x_ = this->x_ / multiple;
		temp.y_ = this->y_ / multiple;
		return temp;
	}

	inline Vector2 operator/(const Vector2& input)const {
		Vector2 temp;
		temp.x_ = this->x_ / input.x_;
		temp.y_ = this->y_ / input.y_;
		return temp;
	}

	inline Vector2 operator+=(const Vector2 &input) {
		this->x_ += input.x_;
		this->y_ += input.y_;
		return *this;
	}

	inline Vector2 operator-=(const Vector2 &input) {
		this->x_ -= input.x_;
		this->y_ -= input.y_;
		return *this;
	}

	inline Vector2 operator*=(const float &multiple) {
		this->x_ *= multiple;
		this->y_ *= multiple;
		return *this;
	}

	inline Vector2 operator/=(const float &multiple) {
		this->x_ /= multiple;
		this->y_ /= multiple;
		return *this;
	}
#endif

//常用方法
#if 1
	inline static Vector2 negation(const Vector2 &input) {
		return Vector2(-input.x_, -input.y_);
	}

	inline static Vector2 lerp(const Vector2 &begin, const Vector2 &end, const float &percentage) {
		return approach(begin, end) ? end : (begin + ((end - begin) * percentage));
	}

	inline static float backEaseIn(float begin_time, const float &delta_time,
		const float &begin, const float &end, const float &k = 0.5f) {

		if (begin_time > delta_time) begin_time = delta_time;
		float&& t = begin_time / delta_time;
		float&& y = powf(t, 3) - k * t * sinf(t * XPI);
		return y * end + begin;
	}

	inline static float backEaseOut(float begin_time, const float& delta_time,
		const float& begin, const float& end, const float& k = 0.5f) {

		if (begin_time > delta_time) begin_time = delta_time;
		float&& t = (begin_time - delta_time) / delta_time;
		float&& y = powf(t, 3) + k * t * sinf(t * XPI) + 1;
		return y * end + begin;
	}

	inline static float model(const Vector2 &input) {
		float temp = (float)sqrtf(powf(input.x_, 2) + powf(input.y_, 2));
		return temp;
	}

	inline static bool approach(const Vector2& vec0, const Vector2& vec1) {
		Vector2 &&temp = vec0 - vec1;
		float &&d = powf(temp.x_, 2) + powf(temp.y_, 2);
		return (d < 0.001f);
	}

	inline static float distance(const Vector2& vec0, const Vector2& vec1) {
		Vector2 &&temp = vec0 - vec1;
		float d = sqrtf(powf(temp.x_, 2) + powf(temp.y_, 2));
		return d;
	}
	
#endif

	float x_, y_;
};

class XTransform
{
public:
	Vector2					location_;
	float					rotation_;
	Vector2					scale_;

	//使用z_Index控制渲染优先级，z_Index越大越显示在上层，z_index ∈ (-100,100]
	float					z_Index_;

	glm::mat4				physics_mat4_;
private:
	btVector3				location_phys_;
	float					rotation_phys_;

public:
	XTransform();
	XTransform(const Vector2 &location, const float &rotation, const Vector2 &scaled);
	XTransform(const XTransform& input);
	~XTransform();

	inline XTransform operator=(const XTransform &input) {
		this->location_ = input.location_;
		this->rotation_ = input.rotation_;
		this->scale_ = input.scale_;
		return *this;
	}

	inline bool operator== (const XTransform &input) const {
		return(this->location_ == input.location_ &&
			this->rotation_ == input.rotation_ &&
			this->scale_ == input.scale_);
	}

	inline void translate(const Vector2 &location) {
		location_ += location;
	}

	inline void rotate(const float &rotation) {
		rotation_ += rotation;
	}

	inline void scale(const Vector2& scaled) {
		scale_ += scaled;
	}

	inline void setZIndex(const float& z_index) {
		if (z_index > 1.0f) z_Index_ = 1.0f;
		else if (z_index < -1.0f) z_Index_ = -1.0f;
		else z_Index_ = z_index;
	}

#if 1
	
	inline void setTransFromBtTrans(const btVector3 &location, const float &rotation) {
		location_.x_ += location.x();
		location_.y_ += location.y();
		rotation_ += rotation;
	}

	inline void setTransFromBtTrans(const btTransform& trans) {
		location_.x_ = trans.getOrigin().x();
		location_.y_ = trans.getOrigin().y();
		rotation_ = getEulerAngle(trans);
	}
#endif

	inline glm::mat4 getWorldTransMat4() const {
		glm::mat4 trans_mat4(1.0f);

		trans_mat4 = glm::translate(trans_mat4, glm::vec3(location_.x_, location_.y_, -z_Index_));
		trans_mat4 = glm::rotate(trans_mat4, glm::radians(rotation_), glm::vec3(0.0f, 0.0f, 1.0f));
		trans_mat4 = glm::scale(trans_mat4, glm::vec3(scale_.x_, scale_.y_, 0.0f));

		return trans_mat4;
	}

	inline glm::mat4 getTRMat4() const {
		glm::mat4 mat4_temp(1.0f);
		mat4_temp = glm::translate(mat4_temp, glm::vec3(location_.x_, location_.y_, 0.0f));
		mat4_temp = glm::rotate(mat4_temp, glm::radians(rotation_), glm::vec3(0.0f, 0.0f, 1.0f));

		return mat4_temp;
	}

	static inline float getEulerAngle(const btTransform &transform) {
		float Y = 0, P = 0, R = 0;
		transform.getBasis().getEulerYPR(Y, P, R);
		return 90.0f * Y;
	}

	static inline btQuaternion eulerToQuaternion(const float &yaw) {
		btQuaternion quaternion = btQuaternion(btVector3(0, 0, 1.0f), yaw / 90.0f);
		return quaternion;
	}

};

#endif 


