#include "reconstruction_thread.h"

reconstruction_thread::reconstruction_thread(pcl::PolygonMesh::Ptr mesh)
{
    newMesh = pcl::PolygonMesh::Ptr mesh;

    //Calling Reconstruction class
    recproject  =  new Cloud_Mesh(newMesh) ;
}

void reconstruction_thread::run()
{

    //If Greedy algorithm is chosen
    if(Database->getRecSettingsStatus()==2)
        Database->m_Mesh = recproject->reconstruction(false,Database);
    //If Poisson algorithm is chosen
    else
        Database->m_Mesh = recproject->reconstruction(true,Database);

    Database->setReconstructionState(1);

}
