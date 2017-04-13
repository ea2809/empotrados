<?php

namespace App;

use Illuminate\Database\Eloquent\Model;

class Codigo extends model
{
    /**
     * The attributes that are mass assignable.
     *
     * @var array
     */
    protected $fillable = [
        'code', 'user_id'
    ];

    /**
     * The attributes that should be hidden for arrays.
     *
     * @var array
     */
    protected $hidden = [
        'id',
    ];

    public function user()
    {
        return $this->belongsTo('App\User');
    }
}
