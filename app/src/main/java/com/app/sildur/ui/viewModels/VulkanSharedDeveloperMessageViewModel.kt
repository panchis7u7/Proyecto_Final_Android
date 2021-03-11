package com.app.sildur.ui.viewModels

import androidx.lifecycle.LiveData
import androidx.lifecycle.MutableLiveData
import androidx.lifecycle.ViewModel

class VulkanSharedDeveloperMessageViewModel : ViewModel() {

    private var _m_extensions: MutableLiveData<String> = MutableLiveData<String>("NULL")
    //Expose read-only data to fragments.
    var m_extensions: LiveData<String> = _m_extensions

    fun setExtensions(ext: String){
        _m_extensions.value = ext
    }

}