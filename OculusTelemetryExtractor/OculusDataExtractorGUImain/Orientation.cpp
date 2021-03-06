#include "stdafx.h"
#include "Orientation.h"

Orientation::Orientation() {
	initOrientationValues(pose);
	initPositionValues(pose);
	yaw = 0;
	pitch = 0;
	roll = 0;
	getType().clear();
}

Orientation::Orientation(const std::string& str) : Telemetry(str) {}

Orientation::~Orientation() {}

void Orientation::initOrientationValues(ovrPosef& p) {
	p.Orientation.w = 0;
	p.Orientation.x = 0;
	p.Orientation.y = 0;
	p.Orientation.z = 0;
}

void Orientation::initPositionValues(ovrPosef& p) {
	p.Position.x = 0;
	p.Position.y = 0;
	p.Position.z = 0;
}

void Orientation::setData(ovrSession& hmd, ovrTrackingState& trackState, CWnd* mainDlg_) {
	mainDlg = mainDlg_;
	trackState = ovr_GetTrackingState(hmd, ovr_GetTimeInSeconds() + 0.005, ovrTrue);
	if (trackState.StatusFlags & (ovrStatus_OrientationTracked | ovrStatus_PositionTracked)) {
		pose = trackState.HeadPose.ThePose;
		quaternion = pose.Orientation;
		quaternion.GetEulerAngles<Axis_Y, Axis_X, Axis_Z>(&yaw, &pitch, &roll);
	}
}

void Orientation::writeToFile(std::ostream& output, CWnd* mainDlg, LVITEMW rowItem) const {
	//Output to file
	output << RadToDegree(yaw) << "," << RadToDegree(pitch) << "," << RadToDegree(roll) << ",";
	std::stringstream stream;
	stream << RadToDegree(yaw);
	addToColumn(mainDlg, stream.str(), _T("YAW"), rowItem);
	stream.str(std::string());
	stream << RadToDegree(pitch);
	addToColumn(mainDlg, stream.str(), _T("PITCH"), rowItem);
	stream.str(std::string());
	stream << RadToDegree(roll);
	//Add stream to column in live table
	addToColumn(mainDlg, stream.str(), _T("ROLL"), rowItem);
}
