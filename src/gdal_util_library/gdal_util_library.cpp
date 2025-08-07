#include <cpp_sandbox/gdal_util_library.hpp>
#include <gdal.h>
#include <gdal_priv.h>
#include <gdal_alg.h>
#include <gdalwarper.h>

void testGDALAutoCreateWarpedVRT()
{
    GDALAllRegister();

    GDALDatasetH dataset = GDALOpen("/home/luke/workspace/cpp/gdal/autotest/gdrivers/data/small_world.tif", GA_ReadOnly);
    if (dataset == nullptr) {
        printf("Failed to open dataset.\n");
        return;
    }
    printf("Dataset opened successfully.\n");

    GDALDatasetH warpedDataset = GDALAutoCreateWarpedVRT(dataset, nullptr, nullptr, GRA_NearestNeighbour, 1.0, nullptr);
    if (warpedDataset == nullptr) {
        printf("Failed to create warped dataset.\n");
        GDALClose(dataset);
        return;
    }
    printf("Warped dataset created successfully.\n");

    void* transformerArg = GDALCreateGenImgProjTransformer2(dataset, warpedDataset, nullptr);
    GDALDestroyTransformer(transformerArg);

    GDALClose(warpedDataset);
    GDALClose(dataset);
}
