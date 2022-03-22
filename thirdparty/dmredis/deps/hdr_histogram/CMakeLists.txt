add_library(hdr_histogram
        hdr_histogram.c
        )
target_link_libraries(hdr_histogram
PRIVATE m
)