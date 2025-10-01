R__LOAD_LIBRARY(libcalibrator)
R__LOAD_LIBRARY(libktracker)
R__LOAD_LIBRARY(libdimu_ana_rus)

int test( const int n_evt=0)
{
    int run_id =5433;
    recoConsts* rc = recoConsts::instance();
    rc->set_IntFlag("RUNNUMBER", run_id);
    rc->set_DoubleFlag("FMAGSTR", -1.044);
    rc->set_DoubleFlag("KMAGSTR", -1.025);

    Fun4AllServer* se = Fun4AllServer::instance();
    se->setRun(run_id);
    //se->Verbosity(1);

    //CalibHodoInTime* cal_hodo = new CalibHodoInTime();
    //cal_hodo->SkipCalibration();
    //cal_hodo->DeleteOutTimeHit();
    //se->registerSubsystem(cal_hodo);

    CalibDriftDist* cal_dd = new CalibDriftDist();
    //cal_dd->Verbosity(999);
    //cal_dd->DeleteOutTimeHit();
    se->registerSubsystem(cal_dd);

    SQReco* reco = new SQReco();
    //reco->Verbosity(99);
    reco->set_legacy_rec_container(false); // default = true
    reco->set_geom_file_name((string)gSystem->Getenv("E1039_RESOURCE") + "/geometry/geom_run005433.root");
    reco->set_enable_KF(true);
    reco->setInputTy(SQReco::E1039);
    reco->setFitterTy(SQReco::KFREF);
    reco->set_evt_reducer_opt("none"); // "ahs"
    reco->set_enable_eval_dst(true);
    for (int ii = 0; ii <= 3; ii++) reco->add_eval_list(ii);
    reco->set_enable_eval(true);
    reco->set_eval_file_name("eval.root");
    se->registerSubsystem(reco);

    SQVertexing* vtx = new SQVertexing();
    vtx->Verbosity(99);
    //vtx->set_legacy_rec_container(true); // default = false
    //vtx->set_single_retracking(true);
    se->registerSubsystem(vtx);

    //Fun4AllInputManager* in = new Fun4AllDstInputManager("DSTIN");
    //se->registerInputManager(in);
    //in->fileopen(DST_in);

    Fun4AllRUSInputManager* in = new Fun4AllRUSInputManager("VectIn");
    in->set_tree_name("tree");
    in->fileopen("RUS_DY.root");
    se->registerInputManager(in);


    //Fun4AllDstOutputManager* out = new Fun4AllDstOutputManager("DSTOUT", DST_out);
    //se->registerOutputManager(out);

    se->run(50);
    se->End();
    //rc->WriteToFile("recoConsts.tsv");
    delete se;
    exit(0); //return 0;
}
