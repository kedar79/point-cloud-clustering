#include <iostream>
#include <string>
#include <vector>

#include "dataset_generation/extract_point_cloud_objects.h"
#include "dataset_generation/json.hpp"

using json = dataset_generation::json;

/**
 * Visualizes objects in PCD file, loading PCD and JSON directly from file. 
 * Use this for debugging!
*/
void visualize_pcd_and_objects(
    dataset_generation::ExtractPointCloudObjects& epco,
    std::string in_pcd_path,
    std::string in_json_path)
{
    pcl::PCLPointCloud2 in_cloud_blob;
    pcl::io::loadPCDFile(in_pcd_path, in_cloud_blob);

    std::ifstream dets3d_file(in_json_path);
    json dets3d_json;
    dets3d_file >> dets3d_json;

    epco.visualize_objects_in_pcd(in_cloud_blob, dets3d_json);
}

/**
 * This node is used for creation of the dataset. It takes in the raw PCD files and uses the ExtractPointCloudsObjects
 * class to extract and save Point Cloud objects
*/

int main(int argc, char** argv)
{
    /**
     * Extract objects into individual PCDs. 
    */

    std::string bag_name = "testbag1_2020-05-09-19-39-52.bag";

    std::string in_folder_pcd =
        "/home/deepak/Dropbox/SJSU/Semesters/Spring2020/CMPE 255/Project/raw_msgs/" + bag_name + "/pcd";
    
    std::string in_folder_dets3d =
        "/home/deepak/Dropbox/SJSU/Semesters/Spring2020/CMPE 255/Project/raw_msgs/" + bag_name + "/detections_3d";

    std::string out_folder_pcd =
        "/home/deepak/Dropbox/SJSU/Semesters/Spring2020/CMPE 255/Project/raw_msgs/" + bag_name + "/out_300_transformed";

    dataset_generation::ExtractPointCloudObjects epco1(
        in_folder_pcd,
        in_folder_dets3d,
        out_folder_pcd);
    
    int min_nb_points_threshold = 300;
    epco1.extract_objects_from_all_pcds(min_nb_points_threshold);

    std::cout << "<======== Objects Extracted 1 =========>" << std::endl;

    out_folder_pcd =
        "/home/deepak/Dropbox/SJSU/Semesters/Spring2020/CMPE 255/Project/raw_msgs/" + bag_name + "/out_500_transformed";

    min_nb_points_threshold = 500;
    dataset_generation::ExtractPointCloudObjects epco2(
        in_folder_pcd,
        in_folder_dets3d,
        out_folder_pcd);
    
    epco2.extract_objects_from_all_pcds(min_nb_points_threshold);

    std::cout << "<======== Objects Extracted 2 =========>" << std::endl;

    /**
     * Combine individual objects into concatenated PCDs
    */
    // std::string combined_pcds_folder = 
    //     "/home/deepak/Dropbox/SJSU/Semesters/Spring2020/CMPE 255/Project/raw_msgs/bag5_2020-05-05-15-11-17.bag/combined_objects_icp_10_pcd";
    
    // // std::string source_pcd_Hatchback = 
    // //     "/home/deepak/Dropbox/SJSU/Semesters/Spring2020/CMPE 255/Project/raw_msgs/bag5_2020-05-05-15-11-17.bag/source_object_clouds/Hatchback_source.pcd";

    // std::string source_pcd_Hatchback = 
    //     "/home/deepak/Dropbox/SJSU/Semesters/Spring2020/CMPE 255/Project/raw_msgs/bag5_2020-05-05-15-11-17.bag/combined_objects_10_pcd/Hatchback_10_combined.pcd";
    
    // // std::vector<std::string> objects = {"Jeep", "Hatchback", "Sedan", "SchoolBus", "SUV"};
    // std::vector<std::string> objects = {"Hatchback"};
    // for (const std::string& object : objects)
    // {
    //     epco.concatenate_objects_with_icp_and_save(
    //         out_folder_pcd,
    //         object,
    //         source_pcd_Hatchback,
    //         combined_pcds_folder,
    //         0.2);
    //     std::cout << "Created combined " << object << " PCD" << std::endl;
    // }

    return 0;
}