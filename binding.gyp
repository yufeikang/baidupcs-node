{
  'targets': [{
    'target_name': 'baidupcs',
    'sources': [
      'src/baidu_pcs.cpp',
      'BaiduPCS/pcs/pcs.c',
      'BaiduPCS/pcs/pcs_http.c',
      'BaiduPCS/pcs/pcs_mem.c',
      'BaiduPCS/pcs/err_msg.c',
      'BaiduPCS/pcs/cJSON.c',
      'BaiduPCS/pcs/pcs_buffer.c',
      'BaiduPCS/pcs/pcs_fileinfo.c',
      'BaiduPCS/pcs/pcs_pan_api_resinfo.c',
      'BaiduPCS/pcs/pcs_passport_dv.c',
      'BaiduPCS/pcs/pcs_slist.c',
      'BaiduPCS/pcs/pcs_utils.c',
      'BaiduPCS/pcs/utf8.c',
    ],
    'include_dirs': [
      '<!(node -e "require(\'nan\')")',
      'BaiduPCS/pcs/',
      '<!@(node "<(module_root_dir)/tools/curl-config.js" --cflags | sed s/-I//g)'
    ],
     'libraries': [
       '<!@(node "<(module_root_dir)/tools/curl-config.js" --libs)'
    ],
   }
  ],
}