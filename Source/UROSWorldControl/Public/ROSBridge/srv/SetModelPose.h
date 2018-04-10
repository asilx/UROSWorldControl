#pragma once

#include "ROSBridgeSrv.h"
#include "InstanceId.h"
#include "Pose.h"

class UROSBRIDGE_API FROSBridgeSetModelPoseSrv : public FROSBridgeSrv {
protected:
	FString Type;

public:
	FROSBridgeSetModelPoseSrv(FString Type_)
	{
		Type = Type_;
	}

	class Request : public SrvRequest {
	private:
		unreal_msgs::InstanceId InstanceId;
		geometry_msgs::Pose Pose;

	public:
		Request() {}
		unreal_msgs::InstanceId GetInstanceId() { return InstanceId; };

		FVector GetLocation()
		{
			return Pose.GetPosition().GetVector();
		}

		FRotator GetRotator()
		{
			return FRotator::FRotator(Pose.GetOrientation().GetQuat());
		}

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override
		{
			InstanceId.FromJson(JsonObject->GetObjectField("instance_id"));
			Pose.FromJson(JsonObject->GetObjectField("pose"));
		}

		static Request GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			Request req;
			req.FromJson(JsonObject);
			return req;
		}

		virtual FString ToString() const override
		{
			return TEXT("FROSBridgeSetModelPoseSrv::Request { InstanceID = ") + InstanceId.ToString() +
				TEXT(", Location = ") + Pose.GetPosition().GetVector().ToString() + 
				TEXT(" and Rotator  = ") + FRotator::FRotator(Pose.GetOrientation().GetQuat()).ToString() + 
				TEXT("} ");

		}

		virtual TSharedPtr<FJsonObject> ToJsonObject() const
		{
			TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
			Object->SetObjectField("instance_id", InstanceId.ToJsonObject());
			Object->SetObjectField("pose", Pose.ToJsonObject());

			return Object;
		}

	};


	class Response : public SrvResponse {
	private:
		bool bSuccess;

	public:
		Response() {}
		Response(bool succeded_) : bSuccess(succeded_) {}
		bool GetSuccess() const { return bSuccess; }
		void SetSuccess(bool Success) { bSuccess = Success; }

		virtual void FromJson(TSharedPtr<FJsonObject> JSonObject) override
		{
			bSuccess = JSonObject->GetBoolField("success");
		}

		static Response GetFromJson(TSharedPtr<FJsonObject> JSonObject)
		{
			Response resp;
			resp.FromJson(JSonObject);
			return resp;
		}

		virtual FString ToString() const override
		{
			return TEXT("FROSBridgeSetModelPoseSrv::Request { %s }"), bSuccess ? TEXT("True") : TEXT("False");
		}

		virtual TSharedPtr<FJsonObject> ToJsonObject() const
		{
			TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
			Object->SetBoolField("success", bSuccess);
			return Object;
		}
	};
};