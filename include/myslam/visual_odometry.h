#pragma once
#ifndef MYSLAM_VISUAL_ODOMETRY_H
#define MYSLAM_VISUAL_ODOMETRY_H

#include "myslam/backend.h"
#include "myslam/common_include.h"
#include "myslam/IO.h"
#include "myslam/frontend.h"
#include "myslam/viewer.h"


namespace simpleslam {

/**
 * VO 对外接口
 */
class VisualOdometry {
public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW;
    typedef std::shared_ptr<VisualOdometry> Ptr;

    /// constructor with config file
    VisualOdometry(std::string &config_path);

    /**
     * do initialization things before run
     * @return true if success
     */
    bool Init();

    /**
     * start vo in the dataset
     */
    void Run();

    /**
     * Make a step forward in dataset
     */
    bool Step();

    /// 获取前端状态
    FrontendStatus GetFrontendStatus() const { return frontend_->GetStatus(); }
    void SavePose(bool flag) {save_pose_ = flag;}
    void SavePointCloud(bool flag) {save_point_cloud=flag;}
    void SetRealtime(bool flag){realtime_=flag;}
private:
    bool inited_ = false;
    bool save_pose_=false;
    bool save_point_cloud = false;
    bool realtime_ = false;

    std::string config_file_path_;

    Frontend::Ptr frontend_ = nullptr;
    Backend::Ptr backend_ = nullptr;
    Map::Ptr map_ = nullptr;
    Viewer::Ptr viewer_ = nullptr;

    // dataset
    IO::Ptr io_ = nullptr;

#ifdef TEST_PERFORMANCE
    // For performance testing only
    double timer1=0;
    double timer2=0;
    double timer3=0;

#endif

};
}  // namespace myslam

#endif  // MYSLAM_VISUAL_ODOMETRY_H
