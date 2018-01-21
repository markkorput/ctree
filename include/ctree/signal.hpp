#pragma once

// #define CTREE_USES_BOOST 1
#define CTREE_USES_CINDER 1

#ifdef CTREE_USES_BOOST
  // #include <boost/signals2>
#endif

#ifdef CTREE_USES_CINDER
  #include "cinder/Signals.h"
#endif

namespace ctree {

  #ifdef CTREE_USES_CINDER
    template <typename Signature>
    class Signal : public cinder::signals::Signal<Signature> {

    };
  #endif
}
