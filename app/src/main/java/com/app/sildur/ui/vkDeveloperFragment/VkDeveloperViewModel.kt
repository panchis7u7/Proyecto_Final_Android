package com.app.sildur.ui.vkDeveloperFragment

import androidx.lifecycle.LiveData
import androidx.lifecycle.MutableLiveData
import androidx.lifecycle.ViewModel

class VkDeveloperViewModel :  ViewModel() {
    private val _text = MutableLiveData<String>().apply {
        value = "This is the developer section"
    }
    val text: LiveData<String> = _text
}