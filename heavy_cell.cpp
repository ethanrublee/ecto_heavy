#include <ecto/ecto.hpp>
#include <opencv2/core/core.hpp>
#include <boost/format.hpp>
#include <boost/shared_ptr.hpp>
#include <iostream>
#include "heavy_magick.hpp"

namespace heavy
{

using ecto::tendrils;
namespace
{
 const char* input_fmt = "in_%04d";
 const char* output_fmt = "out_%04d";
}
struct Heavy
{
  static void declare_params(tendrils& p)
  {
    p.declare<std::string> ("operator","The heavy operator.").required(true);
    p.declare<int> ("n_in","Number of inputs.",1);
    p.declare<int> ("n_out","Number of outputs.",1);
  }
  static void declare_io(const tendrils& p, tendrils& in, tendrils& out)
  {
    int n_in, n_out;
    p.at("n_in") >> n_in;
    p.at("n_out") >> n_out;
    for(int i = 0; i < n_in; ++i)
      in.declare<cv::Mat>(boost::str(boost::format(input_fmt)%i), "An input channel.");
    for(int i = 0; i < n_out; ++i)
      out.declare<cv::Mat>(boost::str(boost::format(output_fmt)%i), "An output channel.");
  }
  void configure(tendrils& p, tendrils& in, tendrils& out)
  {
    std::string soname;
    p["operator"] >> soname;
    heavy_.reset(new HeavyHandle(soname));
    int n_in, n_out;
    p["n_in"] >> n_in;
    p["n_out"] >> n_out;
    for(int i = 0; i < n_in; ++i)
      inputs_.push_back(in.at(boost::str(boost::format(input_fmt)%i)));
    for(int i = 0; i < n_out; ++i)
      outputs_.push_back(out.at(boost::str(boost::format(output_fmt)%i)));

  }
  int process(tendrils& /*in*/, tendrils& /*out*/)
  {
    //TODO foreach cv::Mat in inputs_,outputs_ fill block
    //(*heavy_)(blk,...);
    return ecto::OK;
  }
  boost::shared_ptr<HeavyHandle> heavy_;
  std::vector<ecto::spore<cv::Mat> > inputs_,outputs_;
};

}
ECTO_DEFINE_MODULE(ecto_heavy)
{ }

ECTO_CELL(ecto_heavy, heavy::Heavy, "Heavy", "A heavy cell.");
